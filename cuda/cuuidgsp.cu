/**
 * similar to uuidgrep, only
 * extracting UUIDs from stream of ASCII strings
 * use STREAMS parallel threads for speed
 * @author Denis Kokarev
 */
#include <cstdio>
#include <cstdlib>
#include <errno.h>
#include "die.h"
#include <memory>
#include <cstring>
#include "uuidmatch.h"
#include <cuda_runtime.h>
#include "transpose.cuh"
#include <algorithm>

constexpr int THREADS = 256;
constexpr int STRSZ = 1<<14; // must be under uint16
constexpr int STREAMS = STRSZ;
constexpr char SFILL = ' ';

struct MATCH {
	uint16_t pos;
	uint16_t sz;
};

void prn(const char *ibuf, const MATCH *obuf, const uint16_t *o_sz, const uint16_t rowsz) {
	for (int stream=0; stream<STREAMS; stream++) {
		unsigned sz = o_sz[stream];
		const MATCH *mm = obuf+rowsz*stream;
		const char *s = ibuf+STRSZ*stream;
		for (unsigned i=0; i<sz; i++) {
			if ((fwrite(s+mm[i].pos, 1, mm[i].sz, stdout)) != (int)mm[i].sz)
				die("Write error");
			if (fputc('\n', stdout) != '\n')
				die("Write error");
		}
	}
}

// Convenience function for checking CUDA runtime API results
// can be wrapped around any runtime API call. No-op in release builds.
static cudaError_t checkCuda(cudaError_t result) {
	if (result != cudaSuccess)
		die("CUDA Runtime Error: %s\n", cudaGetErrorString(result));
	return result;
}

// start with automate position 0
inline __device__ void cuda_um_init(UMSTATE *state) {
	*state = 0;
}

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
__global__ void detect(MATCH *odata, const char *idata, uint16_t *d_nmatch, uint16_t nrows) {
	int col = blockIdx.x * blockDim.x + threadIdx.x;
	int iofs = col;
	int oofs = col;
	int stride = gridDim.x * blockDim.x;
	uint16_t nmatch = 0;
	uint16_t row;
	UMSTATE state;
	cuda_um_init(&state);
	for (row=0; row<nrows; row++,iofs+=stride) {
		if (cuda_um_match(&state, idata[iofs])) {
			odata[oofs] = MATCH {uint16_t(row-UMPATLEN+1), UMPATLEN};
			oofs += stride;
			nmatch++;
			//printf("found uuid at row %d\n", row);
		}
	}
	d_nmatch[col] = nmatch;
}

class CudaDetect {
	char *d_ibuf; // original input
	char *d_tibuf; // transposed input
	MATCH *d_tobuf; // transposed output
	MATCH *d_obuf; // regular output
	uint16_t *d_nmatch;
public:
	CudaDetect() {
		checkCuda(cudaMalloc(&d_ibuf, STREAMS*STRSZ*sizeof(*d_ibuf)));
		checkCuda(cudaMalloc(&d_tibuf, STREAMS*STRSZ*sizeof(*d_tibuf)));
		checkCuda(cudaMalloc(&d_tobuf, STREAMS*(STRSZ/UMPATLEN+1)*sizeof(*d_tobuf)));
		checkCuda(cudaMalloc(&d_obuf, STREAMS*(STRSZ/UMPATLEN+1)*sizeof(*d_tobuf)));
		checkCuda(cudaMalloc(&d_nmatch, STREAMS*sizeof(*d_nmatch)));
		checkCuda(cudaMemcpyToSymbol(cuda_uuid_pattern, uuid_pattern, sizeof(uuid_pattern)));
	}
	~CudaDetect() {
		checkCuda(cudaFree(d_ibuf));
		checkCuda(cudaFree(d_tibuf));
		checkCuda(cudaFree(d_tobuf));
		checkCuda(cudaFree(d_obuf));
		checkCuda(cudaFree(d_nmatch));
	}
	void operator()(const char *ibuf, MATCH *obuf, uint16_t *nmatch, uint16_t &rowsz) {
		checkCuda(cudaMemcpy(d_ibuf, ibuf, sizeof(*ibuf)*STRSZ*STREAMS, cudaMemcpyHostToDevice));
		dim3 dimGrid(STRSZ/TRANSPOSE_TILE_DIM, STREAMS/TRANSPOSE_TILE_DIM, 1);
		dim3 dimBlock(TRANSPOSE_TILE_DIM, TRANSPOSE_BLOCK_ROWS, 1);
		transposeNoBankConflicts<<<dimGrid, dimBlock>>>(d_tibuf, d_ibuf);
		checkCuda(cudaGetLastError());
		detect<<<STREAMS/THREADS,THREADS>>>(d_tobuf, d_tibuf, d_nmatch, STREAMS);
		checkCuda(cudaGetLastError());
		checkCuda(cudaMemcpy(nmatch, d_nmatch, sizeof(*nmatch)*STREAMS, cudaMemcpyDeviceToHost));
#if 0
		for (int i=0; i<STREAMS; i++)
			fprintf(stderr, "nmatch[%d] = %d\n", i, nmatch[i]);
#endif
		uint16_t nmx = rowsz = *std::max_element(nmatch, nmatch+STREAMS);
		if (nmx > 0) {
			rowsz = (nmx+TRANSPOSE_TILE_DIM-1)/TRANSPOSE_TILE_DIM*TRANSPOSE_TILE_DIM;
			dim3 dimGrid(STREAMS/TRANSPOSE_TILE_DIM, rowsz/TRANSPOSE_TILE_DIM, 1);
			dim3 dimBlock(TRANSPOSE_TILE_DIM, TRANSPOSE_BLOCK_ROWS, 1);
			transposeNoBankConflicts<<<dimGrid, dimBlock>>>(d_obuf, d_tobuf);
			checkCuda(cudaGetLastError());
			checkCuda(cudaMemcpy(obuf, d_obuf, rowsz*STREAMS*sizeof(obuf[0]), cudaMemcpyDeviceToHost));
		}
	}
};

inline int rfindnl(const char *buf, int sz) {
	int over = 0;
	while (sz > 0 && buf[sz-1] != '\n')
		sz--, over++;
	return over;
}

int main(int argc, char **argv) {
	int over = 0;
	std::unique_ptr<char[]> up_ibuf(new char[STRSZ*(STREAMS+1)]); // +1 to carry over the remaining of the line
	std::unique_ptr<MATCH[]> up_obuf(new MATCH[STRSZ*(STREAMS)]);
	char *ibuf = up_ibuf.get();
	MATCH *obuf = up_obuf.get();
	uint16_t nmatch[STREAMS];
	CudaDetect cuda_detect;
	// read input and scatter it into STREAMS channels
	while (!feof(stdin)) {
		int ns = 0;
		char *buf = ibuf;
		memcpy(buf, buf+STREAMS*STRSZ, over);
		while (ns < STREAMS) {
			int rsz = STRSZ-over;
			int rc = fread(buf+over, 1, rsz, stdin);
			if (rc == rsz) {
				over = rfindnl(buf, STRSZ);
				if (over == STRSZ)
					die("Line size must be less than %d", STRSZ);
				char *next_buf = buf+STRSZ;
				memcpy(next_buf, buf+STRSZ-over, over);
				memset(buf+STRSZ-over, SFILL, over);
				buf = next_buf;
				ns++;
			} else if (rc < 0) {
				die("read error");
			} else {
				// eof - we didn't get full block
				memset(buf+over+rc, SFILL, STRSZ-over-rc);
				ns++;
				memset(ibuf+STRSZ*ns, SFILL, (STREAMS-ns)*STRSZ); // fill up all unused channels
				break;
			}
		}
		//////// run the batch
		uint16_t rowsz;
		cuda_detect(ibuf, obuf, nmatch, rowsz);
		prn(ibuf, obuf, nmatch, rowsz);
	}
}
