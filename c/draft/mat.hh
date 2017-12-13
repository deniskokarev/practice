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

template<typename N> struct Mat {
	using R = N*;
	int rows, cols, sz;
	std::unique_ptr<N[]> uxp;
	N *x;
	Mat(int _r, int _c):rows(_r),cols(_c),sz(rows*cols),uxp(new N[sz]),x(uxp.get()){}
	R operator[](int r) const {
		return R {x+r*cols};
	}
	void operator -=(const Mat &b) {
		assert(rows == b.rows && cols == b.cols);
		for (int i=0; i<sz; i++)
			x[i] -= b.x[i];
	}
	void operator +=(const Mat &b) {
		assert(rows == b.rows && cols == b.cols);
		for (int i=0; i<sz; i++)
			x[i] += b.x[i];
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
	Mat mul(const Mat &b) const {
		const Mat &a = *this;
		assert(a.cols == b.rows);
		Mat res(a.rows, b.cols);
		for (int r1=0; r1<a.rows; r1++) {
			for (int c2=0; c2<b.cols; c2++) {
				N s = 0;
				for (int c1=0; c1<a.cols; c1++)
					s += a[r1][c1]*b[c1][c2];
				res[r1][c2] = s;
			}
		}
		return res;
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

template<typename N> struct Vec2 : public Mat<N> {
	Vec2():Mat<N>(1,2){}
    N &operator[](int _c) const {
		return ((Mat<N>*)this)->operator[](0)[_c];
	}
	N cross(const Vec2 &b) const {
		const Vec2 &a = *this;
		return a[0]*b[1]-b[0]*a[1];
	}	
};

