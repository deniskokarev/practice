/* ACMP 348 */
/*
 * Our naive Matrix arithmetic
 */
#include <memory>
#include <cassert>

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
	int rows, cols;
	int size;
	std::unique_ptr<N[]> vv;

	Mat(int _r, int _c):rows(_r),cols(_c),size(rows*cols),vv(new N[size]){}
	Mat(const Mat &m):Mat(m.rows,m.cols) {
		std::copy(m.vv.get(), m.vv.get()+size, vv.get());
	}
	Mat(Mat &&m):rows(m.rows),cols(m.cols),vv(std::move(m.vv)){}
	const N* operator[](int r) const {
		return vv.get()+r*cols;
	}
	N* operator[](int r) {
		return vv.get()+r*cols;
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
	Mat minor(int r, int c) const {
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
	Mat adj() const {
		assert(rows == cols);
		Mat a(rows, cols);
		for (int r=0; r<rows; r++) {
			int sign = ((r&1) == 0) ? 1:-1;
			for (int c=0; c<cols; c++) {
				Mat mr = minor(r, c);
				a[c][r] = mr.det()*sign;
				sign *= -1;
			}
		}
		return a;
	}
	Mat mul(const Mat &b) const {
		const Mat &a = *this;
		assert(a.cols == b.rows);
		Mat res(a.rows, b.cols);
		for (int r=0; r<a.rows; r++) {
			for (int c=0; c<b.cols; c++) {
				N s = 0;
				for (int j=0; j<a.cols; j++)
					s += a[r][j]*b[j][c];
				res[r][c] = s;
			}
		}
		return res;
	}
	void operator*=(N n) {
		N *av = vv.get();
		for (int i=0; i<size; i++,av++)
			*av *= n;
	}
	void operator-=(const Mat &b) {
		assert(size == b.size);
		N *av = vv.get();
		const N *bv = b.vv.get();
		for (int i=0; i<size; i++,av++,bv++)
			*av -= *bv;
	}
	void operator+=(const Mat &b) {
		assert(size == b.size);
		N *av = vv.get();
		const N *bv = b.vv.get();
		for (int i=0; i<size; i++,av++,bv++)
			*av += *bv;
	}
	void operator=(const Mat<N> &b) {
		assert(size == b.size);
		std::copy(b.vv.get(), b.vv.get()+size, vv.get());
	}
	N len_sq() const {
		N s = 0;
		const N *av = vv.get();
		for (int i=0; i<size; i++,av++)
			s += (*av)*(*av);
		return s;
	}
	// 1/d won't work properly on integral matrixes
	bool inv(Mat &res) const {
		N d = det();
		if (d != 0) {
			res = adj();
			res *= 1/d;
			return true;
		} else {
			return false;
		}
	}
};

/* actual ACMP 348 solution */
#include <iostream>
#include <algorithm>

using namespace std;

using INT = int64_t;

struct P : public Mat<INT> {
public:
	INT &x, &y;
	P():Mat(1,2),x(vv[0]),y(vv[1]){}
	P(const P &p):Mat(p),x(vv[0]),y(vv[1]){}
	INT cross(const P &b) const {
		return x*b.y - b.x*y;
	}
	INT dot(const P &b) const {
		return x*b.x + b.x*b.y;
	}
	void operator=(const P &b) {
		Mat<INT>::operator=(b);
	}
};

// using parametric line intersection approach
// use integers everywhere
int main(int argc, char **argv) {
	P aa[2];
	cin >> aa[0].x >> aa[0].y;
	cin >> aa[1].x >> aa[1].y;
	P bb[2];
	cin >> bb[0].x >> bb[0].y;
	cin >> bb[1].x >> bb[1].y;
	P va = aa[1];
	va -= aa[0];
	P vb = bb[1];
	vb -= bb[0];
	if (va.x*va.x + va.y*va.y < vb.x*vb.x + vb.y*vb.y) {
		// making va the longest vector
		swap(aa[0], bb[0]);
		swap(aa[1], bb[1]);
		swap(va, vb);
	}
	Mat<INT> mm(2,2);
	Mat<INT> cc(2,1);
	mm[0][0] = va.x;
	mm[0][1] = -vb.x;
	mm[1][0] = va.y;
	mm[1][1] = -vb.y;
	cc[0][0] = bb[0].x-aa[0].x;
	cc[1][0] = bb[0].y-aa[0].y;
	bool rc;
	INT det = mm.det();
	if (det != 0) {
		Mat<INT> adj = mm.adj();
		INT det_sign = (det>0)?1:-1;
		adj *= det_sign;
		const Mat<INT> tt = adj.mul(cc);
		INT det_abs = abs(det);
		if (tt[0][0] >= 0 && tt[0][0] <= det_abs && tt[1][0] >= 0 && tt[1][0] <= det_abs)
			rc = true;
		else
			rc = false;
	} else {
		if (va.x != 0 || va.y != 0) {
			// chk if on the straight line
			P p1 = bb[0];
			p1 -= aa[0];
			P p2 = bb[1];
			p2 -= aa[0];
			if (va.cross(p1) == 0 && va.cross(p2) == 0) {
				INT da[2] = {va.dot(aa[0]), va.dot(aa[1])};
				INT db[2] = {va.dot(bb[0]), va.dot(bb[1])};
				sort(da, da+2);
				sort(db, db+2);
				if (da[0] > db[1] || db[0] > da[1])
					rc = false;
				else
					rc = true; // on the straight line and overlap
			} else {
				rc = false;
			}
		} else {
			// both a and b are points
			if (aa[0].x == bb[0].x && aa[0].y == bb[0].y)
				rc = true;
			else
				rc = false;
		}
	}
	cout << (rc?"Yes":"No") << endl;
}
