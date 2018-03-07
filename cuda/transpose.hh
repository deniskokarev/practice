namespace Match {
	class CudaTranspose {
		const char *ibuf;
		char *obuf;
		int dim;
		char *d_ibuf;
		char *d_obuf;
		bool was_init;
	public:
		CudaTranspose();
		int init(const char *ib, char *ob, int d);
		~CudaTranspose();
		void run();
	};
}
