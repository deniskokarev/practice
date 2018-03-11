#include <cuda_runtime.h>
#include "transpose.hh"
#include "detect.hh"
#include "die.h"
#include <stdio.h>
#include <device_functions.h>
#include <algorithm>

constexpr int THREADS = 128;

// Convenience function for checking CUDA runtime API results
// can be wrapped around any runtime API call. No-op in release builds.
static cudaError_t checkCuda(cudaError_t result) {
	if (result != cudaSuccess)
		die("CUDA Runtime Error: %s\n", cudaGetErrorString(result));
	return result;
}

/**
 * detect a sequence of ascending chars
 */
__global__ void detectSeq(Link *odata, const char *idata, unsigned *d_nlink, unsigned dim) {
	int col = blockIdx.x * blockDim.x + threadIdx.x;
	int ofs = col;
	int len = 0;
	for (unsigned row=0; row<dim; row++,ofs+=dim) {
		if (idata[ofs] == ' ')
			len++;
		odata[ofs].prev = 1;
	}
	d_nlink[col] = col;
}

__global__ void reduceMax(const unsigned *d_in, unsigned *d_out, unsigned dim) {
	__shared__ int rmx[THREADS/32]; // current warp size = 32
 	int col = blockIdx.x * blockDim.x + threadIdx.x;
	int mx = d_in[col];
	for (int mask = warpSize/2; mask > 0; mask /= 2) 
		mx = max(mx, __shfl_xor(mx, mask));
	int w = threadIdx.x / warpSize;
	int lane = threadIdx.x % warpSize;
	if (lane == 0)
		rmx[w] = mx;
	__syncthreads();
	mx = (threadIdx.x < THREADS/warpSize) ? rmx[lane] : 0;
	for (int mask = warpSize/2; mask > 0; mask /= 2) 
		mx = max(mx, __shfl_xor(mx, mask));	
	if (threadIdx.x == 0)
		d_out[blockIdx.x] = mx;
}

Match::Detect::Detect(const char *_d_ibuf):d_ibuf(_d_ibuf),d_obuf(nullptr),obuf(nullptr),d_nlink(nullptr),d_nlink_block(nullptr),width(0) {
}

int Match::Detect::init(Link *ob, int w) {
	obuf= ob;
	width = w;
	if (w%THREADS != 0)
		die("width must be divisible by %d", THREADS);
	int rc;
	if ((rc=cudaMalloc(&d_obuf, w*w*sizeof(Link)))!=0)
		return rc;
	if ((rc=cudaMalloc(&d_nlink, w*sizeof(d_nlink[0])))!=0)
		return rc;
	if ((rc=cudaMalloc(&d_nlink_block, w/THREADS*sizeof(d_nlink[0])))!=0)
		return rc;
	return 0;
}

Match::Detect::~Detect() {
	if (d_obuf)
		checkCuda(cudaFree((void*)d_obuf));
	if (d_nlink)
		checkCuda(cudaFree((void*)d_nlink));
	if (d_nlink_block)
		checkCuda(cudaFree((void*)d_nlink_block));
}

unsigned Match::Detect::run() {
	int blocks = width/THREADS;
	detectSeq<<<blocks,THREADS>>>((Link*)d_obuf, (const char*)d_ibuf, d_nlink, width);
	reduceMax<<<blocks,THREADS>>>(d_nlink, d_nlink_block, width);
	reduceMax<<<1,blocks>>>(d_nlink_block, d_nlink_block, width);
	checkCuda(cudaMemcpy(obuf, d_obuf, width*width*sizeof(obuf[0]), cudaMemcpyDeviceToHost));
	checkCuda(cudaMemcpy(&nlinkmax, d_nlink_block, sizeof(unsigned), cudaMemcpyDeviceToHost));
	return nlinkmax;
}
