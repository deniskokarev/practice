#include <iostream>
#include <math.h>
#include <cuda_runtime.h>

// Kernel function to add the elements of two arrays
__global__
void add(int n, float *x, float *y, int chunk_thread) {
	int chunk_block = blockDim.x*chunk_thread;
	int from_n = chunk_block*blockIdx.x + chunk_thread*threadIdx.x;
	int to_n = min(n, from_n+chunk_thread);
	for (int i = from_n; i < to_n; i++)
		y[i] = x[i] + y[i];
}

int main(void) {
	int N = (1<<20);
	float *x, *y;

	// Allocate Unified Memory – accessible from CPU or GPU
	cudaMallocManaged(&x, N*sizeof(float));
	cudaMallocManaged(&y, N*sizeof(float));

	// initialize x and y arrays on the host
	for (int i = 0; i < N; i++) {
		x[i] = 1.0f;
		y[i] = 2.0f;
	}

	int blockSize = 256;
	//int numBlocks = (N + blockSize - 1) / blockSize;
	int numBlocks = 8;
	// Run kernel on 1M elements on the GPU
	const int chunk_thread = (N+numBlocks*blockSize-1)/numBlocks/blockSize;

	add<<<numBlocks, blockSize>>>(N, x, y, chunk_thread);

	// Wait for GPU to finish before accessing on host
	cudaDeviceSynchronize();

	// Check for errors (all values should be 3.0f)
	float maxError = 0.0f;
	for (int i = 0; i < N; i++)
		maxError = fmax(maxError, fabs(y[i]-3.0f));
	std::cout << "Max error: " << maxError << std::endl;

	// Free memory
	cudaFree(x);
	cudaFree(y);
  
	return 0;
}
