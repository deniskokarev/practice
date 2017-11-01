/* ACMP 348 */
/*
 * Our naive Matrix arithmetic
 */
#include <vector>
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
	using VEC = std::vector<N>;
	int rows, cols;
	VEC vv;
	Mat(int _r, int _c):rows(_r),cols(_c),vv(rows*cols){}
	Mat(const Mat &m):rows(m.rows),cols(m.cols),vv(m.vv){}
	Mat(Mat &&m):rows(m.rows),cols(m.cols),vv(std::move(m.vv)){}
	typename VEC::iterator operator[](int r) {
		return vv.begin()+r*cols;
	}
	typename VEC::const_iterator operator[](int r) const {
		return vv.cbegin()+r*cols;
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
		for (auto &v:vv)
			v *= n;
	}
	void operator-=(const Mat &b) {
		assert(vv.size() == b.vv.size());
		for (int i=0; i<vv.size(); i++)
			vv[i] -= b.vv[i];
	}
	void operator+=(const Mat &b) {
		assert(vv.size() == b.vv.size());
		for (int i=0; i<vv.size(); i++)
			vv[i] += b.vv[i];
	}
	void operator=(const Mat<N> &b) {
		assert(vv.size() == b.vv.size());
		copy(b.vv.begin(), b.vv.end(), vv.begin());
	}
	N len_sq() const {
		N s = 0;
		for (auto &v:vv)
			s += v*v;
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
#include <cmath>
#include <algorithm>

using namespace std;

struct P : public Mat<int> {
	int &x, &y;
	P():Mat(1,2),x(vv[0]),y(vv[1]) {}
	int cross(const P &b) const {
		return x*b.y - b.x*y;
	}
};

// using parametric line intersection approach
// use integers everywhere
int main(int argc, char **argv) {
	P aa[2];
	cin >> aa[0].x >> aa[0].y;
	cin >> aa[1].x >> aa[1].y;
	aa[1] -= aa[0];
	P bb[2];
	cin >> bb[0].x >> bb[0].y;
	cin >> bb[1].x >> bb[1].y;
	bb[1] -= bb[0];
	Mat<int> mm(2,2);
	Mat<int> cc(2,1);
	mm[0][0] = aa[1].x;
	mm[0][1] = -bb[1].x;
	mm[1][0] = aa[1].y;
	mm[1][1] = -bb[1].y;
	cc[0][0] = bb[0].x-aa[0].x;
	cc[1][0] = bb[0].y-aa[0].y;
	bool rc;
	int det = mm.det();
	if (det != 0) {
		int det_sign = (det>0)?1:-1;
		int det_abs = abs(det);
		Mat<int> adj = mm.adj();
		Mat<int> tt = adj.mul(cc);
		tt *= det_sign;
		//cerr << "t1: " << tt[0][0] << " t2: " << tt[1][0] << endl;
		if (tt[0][0] >= 0 && tt[0][0] <= det_abs && tt[1][0] >= 0 && tt[1][0] <= det_abs)
			rc = true;
		else
			rc = false;
	} else {
		// chk if on the straight line
		P p1 = bb[0];
		p1 -= aa[0];
		P p2 = bb[1];
		p2 += bb[0];
		p2 -= aa[0];
		if (aa[1].cross(p1) == 0 && aa[1].cross(p2) == 0) {
			int da[2] = {aa[0].x+aa[0].y, aa[0].x+aa[0].y+aa[1].x+aa[1].y};
			int db[2] = {bb[0].x+bb[0].y, bb[0].x+bb[0].y+bb[1].x+bb[1].y};
			sort(da, da+2);
			sort(db, db+2);
			if (da[0] > db[1] || db[0] > da[1])
				rc = false;
			else
				rc = true; // on the straight line and overlap
		} else {
			rc = false;
		}
	}
	cout << (rc?"Yes":"No") << endl;
}
