/* Copyright (c) 1993-2015, NVIDIA CORPORATION. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of NVIDIA CORPORATION nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <cuda_runtime.h>
#include "transpose.hh"
#include "die.h"

// 256 threads altogether
const int TILE_DIM = 32;
const int BLOCK_ROWS = 8;

// Convenience function for checking CUDA runtime API results
// can be wrapped around any runtime API call. No-op in release builds.
static cudaError_t checkCuda(cudaError_t result) {
	if (result != cudaSuccess)
		die("CUDA Runtime Error: %s\n", cudaGetErrorString(result));
	return result;
}

__global__ void copy(char *odata, const char *idata)
{
  int x = blockIdx.x * TILE_DIM + threadIdx.x;
  int y = blockIdx.y * TILE_DIM + threadIdx.y;
  int width = gridDim.x * TILE_DIM;

  for (int j = 0; j < TILE_DIM; j+= BLOCK_ROWS)
    odata[(y+j)*width + x] = idata[(y+j)*width + x];
}

// No bank-conflict transpose
// Same as transposeCoalesced except the first tile dimension is padded 
// to avoid shared memory bank conflicts.
__global__ void transposeNoBankConflicts(char *odata, const char *idata)
{
  __shared__ char tile[TILE_DIM][TILE_DIM+1];
    
  int x = blockIdx.x * TILE_DIM + threadIdx.x;
  int y = blockIdx.y * TILE_DIM + threadIdx.y;
  int width = gridDim.x * TILE_DIM;

  for (int j = 0; j < TILE_DIM; j += BLOCK_ROWS)
     tile[threadIdx.y+j][threadIdx.x] = idata[(y+j)*width + x];

  __syncthreads();

  x = blockIdx.y * TILE_DIM + threadIdx.x;  // transpose block offset
  y = blockIdx.x * TILE_DIM + threadIdx.y;

  for (int j = 0; j < TILE_DIM; j += BLOCK_ROWS)
     odata[(y+j)*width + x] = tile[threadIdx.x][threadIdx.y + j];
}

Match::CudaTranspose::CudaTranspose(const char *ib, char *ob, int d):d_obuf(nullptr),d_ibuf(nullptr),ibuf(ib),obuf(ob),dim(d),err(nullptr) {
	if (d % TILE_DIM == 0) {
		cudaError_t rc;
		if ((rc=cudaMalloc(&d_ibuf, dim*dim))!=0)
			err = cudaGetErrorString(rc);
		if ((rc=cudaMalloc(&d_obuf, dim*dim))!=0)
			err = cudaGetErrorString(rc);
	} else {
		err = "Dimention must be divisible by TILE_DIM";
	}
}

Match::CudaTranspose::operator bool() const {
	return err == nullptr;
}

Match::CudaTranspose::~CudaTranspose() {
	if (d_obuf)
		checkCuda(cudaFree((void*)d_obuf));
	if (d_ibuf)
		checkCuda(cudaFree((void*)d_ibuf));
}

void Match::CudaTranspose::run() {
	dim3 dimGrid(dim/TILE_DIM, dim/TILE_DIM, 1);
	dim3 dimBlock(TILE_DIM, BLOCK_ROWS, 1);
	checkCuda(cudaMemcpy(d_ibuf, ibuf, dim*dim, cudaMemcpyHostToDevice));
	transposeNoBankConflicts<<<dimGrid, dimBlock>>>((char*)d_obuf, (const char*)d_ibuf);
	checkCuda(cudaGetLastError());
	//checkCuda(cudaMemcpy(obuf, d_obuf, dim*dim, cudaMemcpyDeviceToHost));
}
