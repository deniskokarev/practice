/* ACMatP 858 */
#include <iostream>
#include <memory>
#include <cassert>
#include <algorithm>

template<typename I, typename F> void __heaps_perm_r(const I &beg, const I &end, const I &last, F &&f);

// Heap's permutation algorithm via interchanges
// beg->end container will be shuffled (end-beg)! times
// f(beg, end) will be called for every permutation
template<typename I, typename F> void heaps_perm(const I &beg, const I &end, F &&f) {
	__heaps_perm_r(beg, end, end, f);
}

template<typename I, typename F> void __heaps_perm_r(const I &beg, const I &end, const I &last, F &&f) {
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

using namespace std;

template<typename N> struct Mat {
	using R = N*;
	int rows, cols, sz;
	unique_ptr<N[]> uxp;
	N *x;
	Mat(int _r, int _c):rows(_r),cols(_c),sz(rows*cols),uxp(new N[sz]),x(uxp.get()){}
	R operator[](int r) const {
		return R {x+r*cols};
	}
	N det() const {
		assert(rows == cols);
		const Mat &m = *this;
		int pp[rows];
		for (int i=0; i<rows; i++)
			pp[i] = i;
		N sum = 0;
		bool po = true;
		heaps_perm(&pp[0], &pp[cols], [&po, &sum, &m](const int *b, const int *e) {
				N s = 1;
				for (int ri=0; ri<m.rows; ri++)
					s *= m[ri][b[ri]];
				if (po)
					sum += s;
				else
					sum -= s;
				po = !po;
		});
		return sum;
	}
	Mat adj(int r, int c) const {
		const Mat &m = *this;
		Mat res(rows-1, cols-1);
		for (int di=0,si=0; si<rows; si++) {
			if (si == r)
				continue;
			for (int dj=0,sj=0; sj<cols; sj++) {
				if (sj == c)
					continue;
				res[di][dj] = m[si][sj];
				dj++;
			}
			di++;
		}
		return res;
	}
};

int main(int argc, char **argv) {
	// https://math.stackexchange.com/questions/901819/direct-formula-for-area-of-a-triangle-formed-by-three-lines-given-their-equatio
	Mat<int64_t> m(3,3);
	for (int i=0; i<3; i++)
		for (int j=0; j<3; j++)
			cin >> m[i][j];
	int64_t det = m.det();
	if (det != 0) {
		double c[3];
		for (int i=0; i<3; i++)
			c[i] = abs(m.adj(i, 2).det());
		double det2 = det*det;
		double res = det2/2/c[0]/c[1]/c[2];
		cout << res << endl;
	} else {
		cout << 0 << endl;
	}
	return 0;
}
