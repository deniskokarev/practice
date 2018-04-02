#ifndef __TRANSPOSE_CUH__
#define __TRANSPOSE_CUH__

constexpr int TRANSPOSE_TILE_DIM = 32;
constexpr int TRANSPOSE_BLOCK_ROWS = 8;

// No bank-conflict transpose
// Same as transposeCoalesced except the first tile dimension is padded 
// to avoid shared memory bank conflicts.
template <class T> __global__ void transposeNoBankConflicts(T *odata, const T *idata)
{
  __shared__ T tile[TRANSPOSE_TILE_DIM][TRANSPOSE_TILE_DIM+1];
    
  int x = blockIdx.x * TRANSPOSE_TILE_DIM + threadIdx.x;
  int y = blockIdx.y * TRANSPOSE_TILE_DIM + threadIdx.y;
  int width = gridDim.x * TRANSPOSE_TILE_DIM;
  int height = gridDim.y * TRANSPOSE_TILE_DIM;

  for (int j = 0; j < TRANSPOSE_TILE_DIM; j += TRANSPOSE_BLOCK_ROWS)
     tile[threadIdx.y+j][threadIdx.x] = idata[(y+j)*width + x];

  __syncthreads();

  x = blockIdx.y * TRANSPOSE_TILE_DIM + threadIdx.x;  // transpose block offset
  y = blockIdx.x * TRANSPOSE_TILE_DIM + threadIdx.y;

  for (int j = 0; j < TRANSPOSE_TILE_DIM; j += TRANSPOSE_BLOCK_ROWS)
     odata[(y+j)*height + x] = tile[threadIdx.x][threadIdx.y + j];
}

#endif // __TRANSPOSE_CUH__
