/**
 * a-la fgrep utility only in parallel using CUDA
 * grep input lines for precompiled patterns
 * @author Denis Kokarev
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <stdarg.h>
#include <getopt.h>
#include <cuda_runtime.h>
#include "transpose.cuh"
#include "die.h"
#include "par.hh"
#include "act.h"

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
		if (!feof(fin)) {
			if (batch%stages == 0) // wrap the remaining line around
				memcpy(res[0].buf-STRSZ, res[stages-1].buf+STREAMS*STRSZ-STRSZ, STRSZ);
			TRESULT &r = res[batch%stages];
			r.sz = fread(r.buf, 1, STREAMS*STRSZ, fin);
			if (r.sz < 0)
				die("Read error");
			return &r;
		} else {
			return nullptr;
		}
	}
public:
	ReadStage(FILE *fin):PipeHeadExec(), fin(fin) {
		checkCuda(cudaMallocHost(&pinned_buf, STRSZ*STREAMS*stages+STRSZ));
		res[0] = {pinned_buf+STRSZ, 0};
		for (int i=1; i<stages; i++)
			res[i] = {res[i-1].buf+STRSZ*STREAMS, 0};
	}
	~ReadStage() {
		checkCuda(cudaFreeHost(pinned_buf));
	}
};

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
		TRESULT &r = res[batch%stages];
		r.in = *(ReadStage::TRESULT*)arg;
		checkCuda(cudaMemcpyAsync(r.d_ibuf, r.in.buf, r.in.sz, cudaMemcpyHostToDevice, r.stream));
		checkCuda(cudaStreamSynchronize(r.stream));
		return &r;
	}
public:
	CudaH2DStage(PipeHeadExec &parent):PipeStageExec(parent) {
		for (int i=0; i<stages; i++) {
			res[i].in = ReadStage::TRESULT {nullptr, 0};
			checkCuda(cudaMalloc(&res[i].d_ibuf, STREAMS*STRSZ*sizeof(*res[i].d_ibuf)));
			checkCuda(cudaStreamCreate(&res[i].stream));
		}
	}
	~CudaH2DStage() {
		for (int i=0; i<stages; i++) {
			res[i].in = ReadStage::TRESULT {nullptr, 0};
			checkCuda(cudaFree(res[i].d_ibuf));
			checkCuda(cudaStreamDestroy(res[i].stream));
		}
	}
};

struct FGREP_STATE {
	unsigned node;
	int16_t lbeg;	// position where last line started
};

/**
 * consume next char
 * @returns next automata node, where 1 means at root
 * only when at root, it is safe to refresh/reattach the trie
 */
__device__ inline unsigned cuda_act_next_char(const ACT_NODE *act, unsigned node, char ch) {
	unsigned bmask = ch;
	for (int i=0; i<8/ACT_PAGE_P2; i++,bmask >>= ACT_PAGE_P2)
		node = act[node].next[bmask & ((1<<ACT_PAGE_P2)-1)];
	return node;
}

/**
 * iterate the sequence of all matches triggered by last char
 * NB: result_node will be spoiled
 * @return 1 when match was found, *val will be populated with value
 * @return 0 when no more matches
 */
__device__ inline int cuda_act_next_match(const ACT_NODE *act, unsigned *result_node, int *val) {
	if (!act[*result_node].end)
		*result_node = act[*result_node].sufref;
	if (*result_node != ACT_ROOT) {
		*val = act[*result_node].val;
		*result_node = act[*result_node].sufref;
		return 1;
	} else {
		return 0;
	}
}

__global__ void cuda_fgrep(MATCH *match, const char *ibuf, int ibufsz, unsigned *nmatch, const ACT_NODE *act, FGREP_STATE *states) {
	int col = blockIdx.x * blockDim.x + threadIdx.x;
	int stride = gridDim.x * blockDim.x;
	FGREP_STATE &state = states[col];
	//__syncthreads(); // redundant, as the first thread will always run in an earlier block
	if (col == 0)
		state = states[STREAMS-1];
	else
		state = FGREP_STATE {ACT_ROOT, 0};
	MATCH *m = match+col;
	unsigned nm = 0;
	int pos = 0;
	int end_pos = min(ibufsz-STRSZ*col, STRSZ);
	int next_end_pos = min(ibufsz-STRSZ*col, 2*STRSZ);
	const char *p;
	if (col == 0) {
		p = ibuf;
		state = states[STREAMS-1];
	} else {
		for (p=ibuf+col; pos<end_pos && *p!='\n'; p+=stride,pos++);
		if (pos == end_pos)
			return; //die("Lines cannot be longer than %d", int(STRSZ));
		pos++;
		p += stride;
		state = FGREP_STATE {ACT_ROOT, int16_t(pos)};
	}
	while (pos < next_end_pos) {
		state.node = cuda_act_next_char(act, state.node, *p);
		unsigned result_node = state.node;
		int unused;
		if (cuda_act_next_match(act, &result_node, &unused)) {
			while (pos < next_end_pos && *p != '\n') {
				pos++;
				p += stride;
			}
			if (pos == next_end_pos)
				return; //die("Lines cannot be longer than %d", int(STRSZ));
			*m = MATCH {state.lbeg, uint16_t(pos-state.lbeg)};
			nm++;
			m += stride;
			p += stride;
			pos++;
			state.lbeg = pos;
			state.node = ACT_ROOT;
			if (pos > end_pos)
				break;
		} else {
			p += stride;
			pos++;
			if (*p == '\n') {
				if (pos > end_pos) {
					break;
				} else {
					p += stride;
					pos++;
					state.lbeg = pos;
					state.node = ACT_ROOT;
				}
			}
		}
	}
	state.lbeg -= STRSZ;
	states[col] = state;
	nmatch[col] = nm;
}

class CudaFgrep {
	static constexpr int MATCH_RATIO = 10; // lowest ave line len to save mem
	char *d_tibuf; // transposed input
	MATCH *d_tobuf; // transposed output
	MATCH *d_obuf; // regular output
	unsigned *d_nmatch;
	FGREP_STATE *d_state;
	ACT_NODE *d_act;
public:
	CudaFgrep(const ACT *act) {
		checkCuda(cudaMalloc(&d_tibuf, STREAMS*STRSZ*sizeof(*d_tibuf)));
		checkCuda(cudaMalloc(&d_tobuf, STREAMS*(STRSZ/MATCH_RATIO)*sizeof(*d_tobuf)));
		checkCuda(cudaMalloc(&d_obuf, STREAMS*(STRSZ/MATCH_RATIO)*sizeof(*d_tobuf)));
		checkCuda(cudaMalloc(&d_nmatch, STREAMS*sizeof(*d_nmatch)));
		checkCuda(cudaMalloc(&d_state, STREAMS*sizeof(*d_state)));
		FGREP_STATE first_state {ACT_ROOT, 0};
		checkCuda(cudaMemcpy(&d_state[STREAMS-1], &first_state, sizeof(FGREP_STATE), cudaMemcpyHostToDevice));
		checkCuda(cudaMalloc(&d_act, act->sz));
		checkCuda(cudaMemcpy(d_act, act->nodes, act->sz, cudaMemcpyHostToDevice));
	}
	~CudaFgrep() {
		checkCuda(cudaFree(d_tibuf));
		checkCuda(cudaFree(d_tobuf));
		checkCuda(cudaFree(d_obuf));
		checkCuda(cudaFree(d_nmatch));
		checkCuda(cudaFree(d_state));
		checkCuda(cudaFree(d_act));
	}
	void operator()(cudaStream_t stream, const char *d_ibuf, int ibuf_sz, MATCH *obuf, unsigned *nmatch, unsigned &rowsz) {
		dim3 dimGrid(STRSZ/TRANSPOSE_TILE_DIM, STREAMS/TRANSPOSE_TILE_DIM, 1);
		dim3 dimBlock(TRANSPOSE_TILE_DIM, TRANSPOSE_BLOCK_ROWS, 1);
		transposeNoBankConflicts<<<dimGrid, dimBlock, 0, stream>>>(d_tibuf, d_ibuf);
		checkCuda(cudaGetLastError());
		cuda_fgrep<<<STREAMS/THREADS,THREADS,0,stream>>>(d_tobuf, d_tibuf, ibuf_sz, d_nmatch, d_act, d_state);
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

class FgrepStage: public PipeStageExec {
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
	CudaFgrep cfgrep;
	virtual void *next(void *arg) override {
		TRESULT &r = res[batch%stages];
		r.in = *(CudaH2DStage::TRESULT*)arg;
		cfgrep(r.in.stream, r.in.d_ibuf, r.in.in.sz, r.match, r.nmatch, r.match_row_sz);
		return &r;
	}
public:
	FgrepStage(PipeHeadExec &parent, ACT *act):PipeStageExec(parent),cfgrep(act) {
		for (int i=0; i<stages; i++) {
			checkCuda(cudaMallocHost(&res[i].match, sizeof(MATCH)*STRSZ*STREAMS));
			checkCuda(cudaMallocHost(&res[i].nmatch, sizeof(unsigned)*STREAMS));
		}
	}
	~FgrepStage() {
		for (int i=0; i<stages; i++) {
			checkCuda(cudaFreeHost(res[i].match));
			checkCuda(cudaFreeHost(res[i].nmatch));
		}
	}
};

void prn(FILE *fout, const char *ibuf, const MATCH *match, const unsigned *nmatch, const unsigned match_row_sz) {
	for (int stream=0; stream<STREAMS; stream++) {
		unsigned sz = nmatch[stream];
		const MATCH *mm = match+match_row_sz*stream;
		const char *s = ibuf+STRSZ*stream;
		for (unsigned i=0; i<sz; i++) {
			if ((fwrite(s+mm[i].pos, 1, mm[i].sz, fout)) != (int)mm[i].sz)
				die("Write error");
			if (fputc('\n', fout) != '\n')
				die("Write error");
		}
	}
}

static void usage(char *cmd) {
	printf("Match the input strings with actcomp precompiled automata,\n");
	printf("works similar to fgrep\n");
	printf("@author Denis Kokarev\n");
	printf("Usage:\n");
	printf("\t%s patterns.bin <input.txt >filtered.txt\n", cmd);
	printf("patterns.bin - precompiled patterns.txt file, see `actcomp -h`\n");
}

int main(int argc, char **argv) {
	int c;
	opterr = 0;
	while ((c = getopt(argc, argv, "h")) != -1) {
		switch (c) {
		case 'h':
			usage(argv[0]);
			return(0);
		default:
			die("unknown cmd line argument");
		}
	}
	if (argc-optind < 1) {
		usage(argv[0]);
		die("run as `%s patterns.bin <file`", argv[0]);
	}
	ACT act;
	int rc = act_attach_mmap(&act, argv[optind]);
	if (rc != 0)
		die("couldn't use specified patterns file %s, act_attach_mmap() error code %d", argv[optind], rc);
	{
		ReadStage read(stdin);
		CudaH2DStage h2d(read);
		FgrepStage fgrep(h2d, &act);
		for (auto it:PipeOutput(fgrep)) {
			FgrepStage::TRESULT *r = (FgrepStage::TRESULT*)it;
			prn(stdout, r->in.in.buf, r->match, r->nmatch, r->match_row_sz);
		}
	}
	rc = act_detach_mmap(&act);
	if (rc != 0)
		die("act_detach_mmap() error code %d", rc);
}
