#include <iostream>
#include "perm.hh"

#define dim(X)	(sizeof(X)/sizeof(X[0]))

#if (__cplusplus < 201103L)

// C++98 style
struct myprint {
	void operator()(const int *beg, const int *end) const {
		if (end-beg > 0) {
			for (const int *i=beg; i!=end-1; ++i)
				std::cout << *i << ", ";
			std::cout << *(end-1);
		}
		std::cout << std::endl;
	}
};
	
int main(int argc, char **argv) {
	int a[] = {1, 2, 3};
	heaps_perm(&a[0], &a[dim(a)], myprint());
}

#else

// C++11 style
int main(int argc, char **argv) {
	int a[] = {1, 2, 3};
	heaps_perm(&a[0], &a[dim(a)], [](const int *beg, const int *end) -> void {
		if (end-beg > 0) {
			for (auto i=beg; i!=end-1; ++i)
				std::cout << *i << ", ";
			std::cout << *(end-1);
		}
		std::cout << std::endl;
	});
}

#endif
