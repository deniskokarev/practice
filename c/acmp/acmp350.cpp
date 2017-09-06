/* ACMP 350 */
#include <iostream>
#include <algorithm>

/* when next_permutation() is not sporty enough */

template<typename I, typename F> void __heaps_perm_r(const I &beg, const I &end, const I &last, const F &f) {
	if (end-beg == 1) {
		f(beg, last);
	} else if (end-beg > 1) {
		for (I i=beg; i!=(end-1); ++i) {
			__heaps_perm_r(beg, end-1, last, f);
			if ((end-beg)%2) {
				std::swap(*beg, *(end-1));
			} else {
				std::swap(*i, *(end-1));
			}
		}
		__heaps_perm_r(beg, end-1, last, f);
	}
}

// f(beg, end) callback will be invoked for every permutation
template<typename I, typename F> void heaps_perm(const I &beg, const I &end, const F &f) {
	__heaps_perm_r(beg, end, end, f);
}

using namespace std;

int main(int argc, char **argv) {
	string s;
	cin >> s;
	heaps_perm(
		s.begin(),
		s.end(),
		[](const string::iterator &b, const string::iterator &e) {
			for (auto i=b; i!=e; ++i) cout << *i;
			cout << endl;
		}
	); 
	return 0;
}
