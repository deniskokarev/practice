#ifndef __TRANSPOSE_H__
#define __TRANSPOSE_H__

namespace Match {
	class CudaTranspose {
	public:
		char *d_obuf;
		char *d_ibuf;
		const char *ibuf;
		char *obuf;
		int dim;
	public:
		CudaTranspose();
		int init(const char *ib, char *ob, int d);
		~CudaTranspose();
		void run();
	};
}

#endif // __TRANSPOSE_H__
