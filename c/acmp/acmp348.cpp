/* ACMP 348 */
/*
 * "naive" Matrix operations
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
 
template<typename N> class Mat {
protected:
	using VEC = std::vector<N>;
	int rows, cols;
	VEC vv;
public:
	Mat(int _r, int _c):rows(_r),cols(_c),vv(rows*cols) {
	}
	Mat(const Mat &m):rows(m.rows),cols(m.cols),vv(m.vv) {
	}
	Mat(Mat &&m):rows(m.rows),cols(m.cols),vv(std::move(m.vv)) {
	}
	void operator=(const Mat &m) {
		rows = m.rows;
		cols = m.cols;
		vv.resize(m.vv.size());
		std::copy(m.vv.begin(), m.vv.end(), vv.begin());
	}
	void operator=(Mat &&m) {
		rows = m.rows;
		cols = m.cols;
		vv = std::move(m.vv);
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
	bool operator==(const Mat &b) {
		if (vv.size() != b.vv.size())
			return false;
		auto va = vv.begin();
		auto vb = b.vv.begin();
		while (va!=vv.end())
			if (*va++ != *vb++)
				return false;
		return true;
	}
	bool operator!=(const Mat &b) {
		return !operator==(b);
	}
	N dot(const Mat<N> &b) const {
		assert(vv.size() == b.vv.size());
		N s = 0;
		auto va = vv.begin();
		auto vb = b.vv.begin();
		while (va!=vv.end())
			s += (*va++) * (*vb++);
		return s;
	}
	N len_sq() const {
		return dot(*this);
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
	// in case if you want to "name" a cell
	class F {
	protected:
		Mat<N> &parent;
		int ofs;
	public:
		F(Mat &_p, int _ofs):parent(_p), ofs(_ofs){
		}
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
	 
	P():Mat(1,2),x(*this,0),y(*this,1) {
	}
	P(const P &p):P() {
		copy(p.vv.begin(), p.vv.end(), vv.begin());
	}
	// cross (vector) product
	INT cross(const P &b) const {
		return x*b.y - b.x*y;
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
	if (va.len_sq() < vb.len_sq()) {
		// making "a" our longest vector
		swap(aa, bb);
		swap(va, vb);
	}
	// solve parametric line eq
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
		Mat<INT> adj = mm.adj(); // don't divide by det
		INT det_sign = (det>0)?1:-1;
		adj *= det_sign;
		const Mat<INT> tt = adj.mul(cc); // tt is scaled by det_abs
		INT det_abs = abs(det);
		// if both t[0] and t[1] lay in [0..det_abs] range
		rc = (tt[0][0] >= 0 && tt[0][0] <= det_abs && tt[1][0] >= 0 && tt[1][0] <= det_abs);
	} else {
		if (va.x != 0 || va.y != 0) {
			// we know they don't intersect, now chk if on the straight line
			P pb = bb[0];
			pb -= aa[0];
			if (va.cross(pb) == 0) {
				// project both seqments on the va vect (extra scaling by |va| doesn't hurt)
				INT dta[2] = {va.dot(aa[0]), va.dot(aa[1])};
				INT dtb[2] = {va.dot(bb[0]), va.dot(bb[1])};
				sort(dta, dta+2);
				sort(dtb, dtb+2);
				rc = ((dtb[1] >= dta[0] && dtb[0] <= dta[1])); // if overlap
			} else {
				rc = false; // just ||
			}
		} else {
			// both a and b are points
			rc = (aa[0] == bb[0]);
		}
	}
	cout << (rc?"Yes":"No") << endl;
}
