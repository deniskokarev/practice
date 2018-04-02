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
		const char *err;
	public:
		CudaTranspose(const char *ib, char *ob, int d);
		operator bool() const;
		~CudaTranspose();
		void run();
	};
}

#endif // __TRANSPOSE_H__
