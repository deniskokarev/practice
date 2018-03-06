#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cuda_runtime.h>

int main() {
    const unsigned int N = 1048576*16;
    const unsigned int bytes = N * sizeof(int);
    int *h_a;
    int *d_a;
    cudaMalloc((int**)&d_a, bytes);
	cudaError_t status = cudaMallocHost((void**)&h_a, bytes);
	if (status != cudaSuccess)
		printf("Error allocating pinned host memory\n");
 
    memset(h_a, 0, bytes);
    cudaMemcpy(d_a, h_a, bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(h_a, d_a, bytes, cudaMemcpyDeviceToHost);

    return 0;
}
