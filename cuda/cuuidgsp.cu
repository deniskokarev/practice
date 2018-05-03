/**
 * similar to uuidgrep, only
 * extracting UUIDs from stream of ASCII strings
 * use STREAMS parallel threads for speed
 * CUDA version of the tool
 * @author Denis Kokarev
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cuda_runtime.h>
#include "transpose.cuh"
#include "uuidmatch.h"
#include "die.h"
#include "par.hh"

constexpr int THREADS = 256;
constexpr int STRSZ = 1<<14; // must be under int16
constexpr int STREAMS = STRSZ;

struct MATCH {
	int16_t pos;
	uint16_t sz;
};

// Convenience function for checking CUDA runtime API results
// can be wrapped around any runtime API call. No-op in release builds.
#define checkCuda(e) {	if (e!=cudaSuccess) { die("Cuda failure %s:%d: '%s'\n",__FILE__,__LINE__,cudaGetErrorString(e)); } }

// owns input the data buffers for the pipeline
class ReadStage: public PipeHeadExec {
public:
	struct TRESULT {
		char *buf;
		int sz;
	};
private:
	static constexpr int stages = 4; // need to drag the input over 4 pipe segments
	FILE *fin;
	TRESULT res[stages];
	char *pinned_buf;
private:
	virtual void *next() override {
		fprintf(stderr, "start read batch %d\n", batch);
		if (!feof(fin)) {
			if (batch%stages == 0) // wrap the remaining line around
				memcpy(res[0].buf-UMPATLEN, res[stages-1].buf+STREAMS*STRSZ-UMPATLEN, UMPATLEN);
			TRESULT &r = res[batch%stages];
			r.sz = fread(r.buf, 1, STREAMS*STRSZ, fin);
			if (r.sz < 0)
				die("Read error");
			fprintf(stderr, "end read batch %d\n", batch);
			return &r;
		} else {
			fprintf(stderr, "finished read batch %d\n", batch);
			return nullptr;
		}
	}
public:
	ReadStage(FILE *fin):PipeHeadExec(), fin(fin) {
		checkCuda(cudaMallocHost(&pinned_buf, STRSZ*STREAMS*stages+STRSZ));
		res[0] = {pinned_buf+STRSZ, 0};
		for (int i=1; i<stages; i++)
			res[i] = {res[i-1].buf+STRSZ*STREAMS, 0};
		fprintf(stderr, "initialized read\n");
	}
	~ReadStage() {
		checkCuda(cudaFreeHost(pinned_buf));
	}
};

inline __device__ int cuda_ch_category(unsigned char c) {
	if ((c>='0' && c<='9') || (c>='a' && c<='f') || (c>='A' && c<='F'))
		return P_HEX;
	else if (c == '-')
		return P_DASH;
	else
		return P_NONE;
}

__constant__ UMSTATE cuda_uuid_pattern[UMPATLEN+1][P_SZ];

// return true when ch was the last char in uuid pattern
inline __device__ int cuda_um_match(UMSTATE *state, char ch) {
	int cat = cuda_ch_category(ch);
	*state = cuda_uuid_pattern[*state][cat];
	if (*state == UMPATLEN) {
		*state = cuda_uuid_pattern[*state][cat];
		return 1;
	} else {
		return 0;
	}
}

/**
 * detect uuids
 */
__global__ void detect(MATCH *odata, const char *idata, int ibuf_sz, unsigned *d_nmatch, UMSTATE *d_umstate, uint16_t nrows) {
	int col = blockIdx.x * blockDim.x + threadIdx.x;
	int iofs = col;
	int oofs = col;
	int stride = gridDim.x * blockDim.x;
	unsigned nmatch = 0;
	uint16_t row;
	UMSTATE &state = d_umstate[col];
	//__syncthreads(); // redundant, as the first thread will always run in an earlier block
	if (col == 0)
		state = d_umstate[STREAMS-1];
	else
		state = 0;
	int lastrow = min(nrows, ibuf_sz-col*nrows);
	for (row=0; row<lastrow; row++,iofs+=stride) {
		if (cuda_um_match(&state, idata[iofs])) {
			odata[oofs] = MATCH {int16_t(row-UMPATLEN+1), UMPATLEN};
			oofs += stride;
			nmatch++;
		}
	}
	if (col < STREAMS-1) {
		iofs = col+1;
		while (state != 0 && row<lastrow+UMPATLEN) {
			if (cuda_um_match(&state, idata[iofs])) {
				odata[oofs] = MATCH {int16_t(row-UMPATLEN+1), UMPATLEN};
				oofs += stride;
				nmatch++;
				break;
			}
			row++;
			iofs+=stride;
		}
	}
	d_nmatch[col] = nmatch;
}

class CudaH2DStage: public PipeStageExec {
public:
	struct TRESULT {
		ReadStage::TRESULT in;
		char *d_ibuf; // device original input
		cudaStream_t stream;
	};
private:
	static constexpr int stages = 2;
	TRESULT res[stages];
	virtual void *next(void *arg) override {
		fprintf(stderr, "start h2d batch %d\n", batch);
		TRESULT &r = res[batch%stages];
		r.in = *(ReadStage::TRESULT*)arg;
		checkCuda(cudaMemcpyAsync(r.d_ibuf, r.in.buf, r.in.sz, cudaMemcpyHostToDevice, r.stream));
		checkCuda(cudaStreamSynchronize(r.stream));
		fprintf(stderr, "end h2d batch %d\n", batch);
		return &r;
	}
public:
	CudaH2DStage(PipeHeadExec &parent):PipeStageExec(parent) {
		for (int i=0; i<stages; i++) {
			res[i].in = ReadStage::TRESULT {nullptr, 0};
			checkCuda(cudaMalloc(&res[i].d_ibuf, STREAMS*STRSZ*sizeof(*res[i].d_ibuf)));
			checkCuda(cudaStreamCreate(&res[i].stream));
		}
		fprintf(stderr, "initialized h2d\n");
	}
	~CudaH2DStage() {
		for (int i=0; i<stages; i++) {
			res[i].in = ReadStage::TRESULT {nullptr, 0};
			checkCuda(cudaFree(res[i].d_ibuf));
			checkCuda(cudaStreamDestroy(res[i].stream));
		}
	}
};

class CudaDetect {
	char *d_tibuf; // transposed input
	MATCH *d_tobuf; // transposed output
	MATCH *d_obuf; // regular output
	unsigned *d_nmatch;
	UMSTATE *d_umstate;
public:
	CudaDetect() {
		checkCuda(cudaMalloc(&d_tibuf, STREAMS*STRSZ*sizeof(*d_tibuf)));
		checkCuda(cudaMalloc(&d_tobuf, STREAMS*(STRSZ/UMPATLEN+2)*sizeof(*d_tobuf)));
		checkCuda(cudaMalloc(&d_obuf, STREAMS*(STRSZ/UMPATLEN+2)*sizeof(*d_tobuf)));
		checkCuda(cudaMalloc(&d_nmatch, STREAMS*sizeof(*d_nmatch)));
		checkCuda(cudaMalloc(&d_umstate, STREAMS*sizeof(*d_umstate)));
		checkCuda(cudaMemset(d_umstate, 0, STREAMS*sizeof(*d_umstate)));
		checkCuda(cudaMemcpyToSymbol(cuda_uuid_pattern, uuid_pattern, sizeof(uuid_pattern)));
	}
	~CudaDetect() {
		checkCuda(cudaFree(d_tibuf));
		checkCuda(cudaFree(d_tobuf));
		checkCuda(cudaFree(d_obuf));
		checkCuda(cudaFree(d_nmatch));
		checkCuda(cudaFree(d_umstate));
		fprintf(stderr, "initialized cuda detect\n");
	}
	void operator()(cudaStream_t stream, const char *d_ibuf, int ibuf_sz, MATCH *obuf, unsigned *nmatch, unsigned &rowsz) {
		dim3 dimGrid(STRSZ/TRANSPOSE_TILE_DIM, STREAMS/TRANSPOSE_TILE_DIM, 1);
		dim3 dimBlock(TRANSPOSE_TILE_DIM, TRANSPOSE_BLOCK_ROWS, 1);
		transposeNoBankConflicts<<<dimGrid, dimBlock, 0, stream>>>(d_tibuf, d_ibuf);
		checkCuda(cudaGetLastError());
		detect<<<STREAMS/THREADS,THREADS,0,stream>>>(d_tobuf, d_tibuf, ibuf_sz, d_nmatch, d_umstate, STREAMS);
		checkCuda(cudaGetLastError());
		checkCuda(cudaMemcpyAsync(nmatch, d_nmatch, sizeof(*nmatch)*STREAMS, cudaMemcpyDeviceToHost, stream));
		checkCuda(cudaStreamSynchronize(stream));
		unsigned nmx = rowsz = *std::max_element(nmatch, nmatch+STREAMS);
		if (nmx > 0) {
			rowsz = (nmx+TRANSPOSE_TILE_DIM-1)/TRANSPOSE_TILE_DIM*TRANSPOSE_TILE_DIM;
			dim3 dimGrid(STREAMS/TRANSPOSE_TILE_DIM, rowsz/TRANSPOSE_TILE_DIM, 1);
			dim3 dimBlock(TRANSPOSE_TILE_DIM, TRANSPOSE_BLOCK_ROWS, 1);
			transposeNoBankConflicts<<<dimGrid, dimBlock, 0, stream>>>(d_obuf, d_tobuf);
			checkCuda(cudaGetLastError());
			checkCuda(cudaMemcpyAsync(obuf, d_obuf, rowsz*STREAMS*sizeof(obuf[0]), cudaMemcpyDeviceToHost, stream));
			checkCuda(cudaStreamSynchronize(stream));
		}
	}
};

class DetectStage: public PipeStageExec {
public:
	struct TRESULT {
		CudaH2DStage::TRESULT in;
		unsigned match_row_sz;
		MATCH *match;
		unsigned *nmatch;
	};
private:
	static constexpr int stages = 2;
	TRESULT res[stages];
	CudaDetect detect;
	virtual void *next(void *arg) override {
		fprintf(stderr, "start detect batch %d\n", batch);
		TRESULT &r = res[batch%stages];
		r.in = *(CudaH2DStage::TRESULT*)arg;
		detect(r.in.stream,r.in.d_ibuf, r.in.in.sz, r.match, r.nmatch, r.match_row_sz);
		fprintf(stderr, "end detect batch %d\n", batch);
		return &r;
	}
public:
	DetectStage(PipeHeadExec &parent):PipeStageExec(parent),detect() {
		for (int i=0; i<stages; i++) {
			checkCuda(cudaMallocHost(&res[i].match, sizeof(MATCH)*STRSZ*STREAMS));
			checkCuda(cudaMallocHost(&res[i].nmatch, sizeof(unsigned)*STREAMS));
		}
		fprintf(stderr, "initialized detect\n");
	}
	~DetectStage() {
		for (int i=0; i<stages; i++) {
			checkCuda(cudaFreeHost(res[i].match));
			checkCuda(cudaFreeHost(res[i].nmatch));
		}
	}
};

void prn(const char *ibuf, const MATCH *match, const unsigned *nmatch, const unsigned match_row_sz) {
	for (int stream=0; stream<STREAMS; stream++) {
		unsigned sz = nmatch[stream];
		const MATCH *mm = match+match_row_sz*stream;
		const char *s = ibuf+STRSZ*stream;
		for (unsigned i=0; i<sz; i++) {
			if ((fwrite(s+mm[i].pos, 1, mm[i].sz, stdout)) != (int)mm[i].sz)
				die("Write error");
			if (fputc('\n', stdout) != '\n')
				die("Write error");
		}
	}
}

int main(int argc, char **argv) {
	ReadStage read(stdin);
	CudaH2DStage h2d(read);
	DetectStage detect(h2d);
	for (auto it:PipeOutput(detect)) {
		DetectStage::TRESULT *r = (DetectStage::TRESULT*)it;
		prn(r->in.in.buf, r->match, r->nmatch, r->match_row_sz);
	}
}
