#include <cuda_runtime.h>
#include "transpose.hh"
#include "detect.hh"
#include "die.h"
#include <stdio.h>
#include <device_functions.h>
#include <algorithm>

constexpr int THREADS = 256;

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
__global__ void detectSeq(Link *odata, char *idata, unsigned *d_nlink, uint16_t dim) {
	int col = blockIdx.x * blockDim.x + threadIdx.x;
	int ofs = col;
	uint16_t nlink = 0;
	char ch = 0;
	char match = 0;
	Link l;
	l.len = 0;
	l.pos = 0;
	l.next = 0;
	for (uint16_t row=0; row<dim; row++,ofs+=dim) {
		if (idata[ofs] == ch) {
			l.len++;
			match = 1;
		} else {
			if (match) {
				l.len++;
				odata[ofs] = l;
				nlink++;
				l.next = row;
			}
			l.len = 0;
			match = 0;
		}
		ch = idata[ofs]+1;
	}
	d_nlink[col] = nlink;
	if (l.len > 0) {
		l.next = dim;
		l.len++;
	}
	odata[ofs] = l;
	ofs = col+dim*dim;
	int oofs = col+dim*(dim-1);
	uint16_t next = 0;
	uint16_t left = nlink;
	for (uint16_t row=dim-1; row>0; row--,ofs-=dim) {
		if (row == l.next) {
			l = odata[ofs];
			odata[oofs].len = l.len;
			odata[oofs].pos = row-l.len;
			odata[oofs].next = next;
			oofs--;
			left--;
			next = row;
		}
	}
	l.len = 0;
	l.pos = 0;
	l.next = next;
	ofs = dim*dim+col;
	odata[ofs] = l;
}

__global__ void recalcLinksSeq(Link *odata, uint16_t dim, uint16_t nlink) {
	int col = blockIdx.x * blockDim.x + threadIdx.x;
	int zrow = dim-nlink-1;
	int erow = dim;
	Link l = odata[erow*dim+col];
	odata[zrow*dim+col] = l;
	int ofs = zrow*dim+col;
	for (int row=zrow; row<dim; row++,ofs+=dim)
		odata[ofs].next -= zrow;
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
	// since warpSize*warpSize >= THREADS, run second stage right here
	mx = (lane < THREADS / warpSize) ? rmx[lane] : 0;
	for (int mask = warpSize/2; mask > 0; mask /= 2) 
		mx = max(mx, __shfl_xor(mx, mask));	
	if (threadIdx.x == 0)
		d_out[blockIdx.x] = mx;
}

Match::Detect::Detect(const char *_d_ibuf, Link *ob, int w):d_ibuf(_d_ibuf),d_obuf(nullptr),obuf(ob),d_nlink(nullptr),d_nlink_block(nullptr),width(w),err(nullptr) {
	if (w%THREADS == 0) {
		cudaError_t rc;
		if ((rc=cudaMalloc(&d_obuf, (w+1)*w*sizeof(Link))) != 0)
			err = cudaGetErrorString(rc);
		if ((rc=cudaMalloc(&d_nlink, w*sizeof(int))) != 0)
			err = cudaGetErrorString(rc);
		if ((rc=cudaMalloc(&d_nlink_block, w/THREADS*sizeof(int))) != 0)
			err = cudaGetErrorString(rc);
	} else {
		snprintf(errbuf, sizeof(errbuf), "width must be divisible by %d", THREADS);
		err = errbuf;
	}
}

Match::Detect::operator bool() const {
	return err == nullptr;
}

Match::Detect::~Detect() {
	if (d_nlink_block)
		checkCuda(cudaFree((void*)d_nlink_block));
	if (d_nlink)
		checkCuda(cudaFree((void*)d_nlink));
	if (d_obuf)
		checkCuda(cudaFree((void*)d_obuf));
}

unsigned Match::Detect::run() {
	int blocks = width/THREADS;
	detectSeq<<<blocks,THREADS>>>((Link*)d_obuf, (char*)d_ibuf, d_nlink, width);
	checkCuda(cudaGetLastError());
	reduceMax<<<blocks,THREADS>>>(d_nlink, d_nlink_block, width);
	checkCuda(cudaGetLastError());
	reduceMax<<<1,blocks>>>(d_nlink_block, d_nlink_block, width);
	checkCuda(cudaGetLastError());
	checkCuda(cudaMemcpy(&nlinkmax, d_nlink_block, sizeof(unsigned), cudaMemcpyDeviceToHost));
	recalcLinksSeq<<<blocks,THREADS>>>((Link*)d_obuf, width, nlinkmax);
	checkCuda(cudaMemcpy(obuf, d_obuf+(width-nlinkmax)*width, nlinkmax*width*sizeof(obuf[0]), cudaMemcpyDeviceToHost));
	return nlinkmax;
}
