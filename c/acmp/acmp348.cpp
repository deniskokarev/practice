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
	 
	Mat(int _r, int _c):rows(_r),cols(_c),vv(rows*cols) {
	}
	Mat(const Mat &m):rows(m.rows),cols(m.cols),vv(m.vv) {
	}
	Mat(Mat &&m):rows(m.rows),cols(m.cols),vv(std::move(m.vv)) {
	}
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
	Mat matminor(int r, int c) const {
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
				Mat mr = matminor(r, c);
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
		auto va = vv.begin();
		auto vb = b.vv.begin();
		while (va!=vv.end())
			*va++ -= *vb++;
	}
	void operator+=(const Mat &b) {
		assert(vv.size() == b.vv.size());
		auto va = vv.begin();
		auto vb = b.vv.begin();
		while (va!=vv.end())
			*va++ += *vb++;
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
	// in case if want to access some matrix cells by name
	struct F {
		Mat<N> &parent;
		int ofs;
		operator N() const {
			return parent.vv[ofs];
		}
		operator N&() {
			return parent.vv[ofs];
		}
		void operator=(const N &n) {
			parent.vv[ofs] = n;
		}
		void operator=(const F &n) {
			parent.vv[ofs] = n;
		}
	};
};
 
 
/* actual ACMP 348 solution */
#include <iostream>
#include <algorithm>
 
using namespace std;
 
using INT = int64_t;
 
struct P : public Mat<INT> {
	F x, y;
	 
	P():Mat(1,2),x{*this, 0},y{*this, 1} {
	}
	P(const P &p):P() {
		copy(p.vv.begin(), p.vv.end(), vv.begin());
	}
	INT cross(const P &b) const {
		return x*b.y - b.x*y;
	}
	INT dot(const P &b) const {
		return x*b.x + b.x*b.y;
	}
};
 
// Solution from MAXimal
inline int area (const P &a, const P &b, const P &c) {
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}
  
inline bool intersect_1 (INT a, INT b, INT c, INT d) {
	if (a > b)	swap (a, b);
	if (c > d)	swap (c, d);
	return max(a,c) <= min(b,d);
}
 
inline int sign(INT v) {
	return v>0?1:v<0?-1:0;
}
 
bool intersect(const P &a, const P &b, const P &c, const P &d) {
	return intersect_1 (a.x, b.x, c.x, d.x)
		&& intersect_1 (a.y, b.y, c.y, d.y)
		&& sign(area(a,b,c)) * sign(area(a,b,d)) <= 0
		&& sign(area(c,d,a)) * sign(area(c,d,b)) <= 0;
}
 
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
		swap(aa[0].vv, bb[0].vv);
		swap(aa[1].vv, bb[1].vv);
		swap(va.vv, vb.vv);
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
			if (va.cross(p1) == 0) {
				if (intersect_1(aa[0].x, aa[1].x, bb[0].x, bb[1].x) &&
					intersect_1(aa[0].y, aa[1].y, bb[0].y, bb[1].y))
					rc = true; // on the straight line and overlap
				else
					rc = false;
				assert(rc == intersect(aa[0], aa[1], bb[0], bb[1]));
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
