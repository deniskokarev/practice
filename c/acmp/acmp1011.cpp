/* ACMP 1011 */

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
	Mat<N> operator-(const Mat<N> &b) const {
		assert(vv.size() == b.vv.size());
		Mat<N> res(*this);
		res -= b;
		return res;
	}
	Mat<N> operator+(const Mat<N> &b) const {
		assert(vv.size() == b.vv.size());
		Mat<N> res(*this);
		res += b;
		return res;
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

/* actual ACMP 1011 solution */
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

struct P : public Mat<double> {
	double &x, &y;
	P():Mat(1,2),x(vv[0]),y(vv[1]) {}
	P(Mat<double> &&m):Mat(m),x(vv[0]),y(vv[1]) {}
	P(const Mat<double> &m):Mat(m),x(vv[0]),y(vv[1]) {}
	P(double _x, double _y):P() {
		x = _x;
		y = _y;
	}
	void operator=(const P&b) {
		Mat<double>::operator=(b);
	}
	P operator-(const P&b) const {
		return Mat<double>::operator-(b);
	}
	double cross(const P &b) const {
		return x*b.y - y*b.x;
	}
};

// find and print statistical median of 3 values just in case if our triangle
// was severely degenerate and the result is unstable
void prn_median(const P oo[3], double rrv[3]) {  
	double xx[3] = {oo[0].x, oo[1].x, oo[2].x};
	double yy[3] = {oo[0].y, oo[1].y, oo[2].y};
	sort(xx, xx+3);
	sort(yy, yy+3);
	sort(rrv, rrv+3);
	P o(xx[1], yy[1]);
	cout << o.x << " " << o.y << " " << sqrt(rrv[1]) << endl;
}

// Iterate over all vertices and make
// isosceles triangle every time to get mid reference point through
// which the bisect goes
// Then find the point of said bisection intersects
// We're doing it by solving parametric line equation
void i(const P pp[3]) {
	P mid[3];
	for (int i=0; i<3; i++) {
		int j=(i+1)%3;
		int k=(i+2)%3;
		P vj = (pp[j]-pp[i]);
		P vk = (pp[k]-pp[i]);
		double lj = vj.len_sq();
		double lk = vk.len_sq();
		if (lj > lk) {
			vk *= sqrt(lj/lk);
			vk += vj;
			mid[i] = vk;
		} else {
			vj *= sqrt(lk/lj);
			vj += vk;
			mid[i] = vj;
		}
		mid[i] *= .5;
	}
	P oo[3];
	for (int i=0; i<3; i++) {
		int j=(i+1)%3;
		Mat<double> mm(2,2);
		Mat<double> cc(2,1);
		mm[0][0] = mid[i].x;
		mm[0][1] = -mid[j].x;
		mm[1][0] = mid[i].y;
		mm[1][1] = -mid[j].y;
		cc[0][0] = pp[j].x-pp[i].x;
		cc[1][0] = pp[j].y-pp[i].y;
		Mat<double> inv(2,2);
		if (mm.inv(inv)) {
			auto tt = inv.mul(cc);
			oo[i] = P(tt[0][0]*mid[i].x, tt[0][0]*mid[i].y);
			oo[i] += P(tt[1][0]*mid[j].x, tt[1][0]*mid[j].y);
			oo[i] += pp[i];
			oo[i] += pp[j];
			oo[i] *= .5; // average two parameters t1 and t2
		}
	}
	double rrv[3];
	for (int i=0; i<3; i++) {
		int j=(i+1)%3;
		int k=(i+2)%3;
		double cr = (pp[j]-oo[i]).cross(pp[k]-oo[i]);
		rrv[i] = cr*cr/(pp[k]-pp[j]).len_sq();
	}
	prn_median(oo, rrv);	// prn statistical median just in case	
}

// working of the fact that vectors representing sides
// and the radial vector from center to the side must be
// perpendicular (dot product == 0)
void o(const P pp[3]) {
	Mat<double> mm(2,2);
	Mat<double> cc(2,1);
	P oo[3];
	double rrv[3];
	for (int i=0; i<3; i++) {
		int j=(i+1)%3;
		int k=(i+2)%3;
		mm[0][0] = 2*(pp[j].x-pp[i].x);
		mm[0][1] = 2*(pp[j].y-pp[i].y);
		mm[1][0] = 2*(pp[k].x-pp[i].x);
		mm[1][1] = 2*(pp[k].y-pp[i].y);
		cc[0][0] = pp[j].x*pp[j].x-pp[i].x*pp[i].x + pp[j].y*pp[j].y-pp[i].y*pp[i].y;
		cc[1][0] = pp[k].x*pp[k].x-pp[i].x*pp[i].x + pp[k].y*pp[k].y-pp[i].y*pp[i].y;
		Mat<double> inv(2,2);
		if (mm.inv(inv)) {
			auto res = inv.mul(cc);
			oo[i] = P(res[0][0], res[1][0]);
			P rv = pp[i];
			rv -= oo[i];
			rrv[i] = rv.len_sq();
		}
	}
	prn_median(oo, rrv);	// prn statistical median just in case
}

int main(int argc, char **argv) {
	P pp[3];
	for (int i=0; i<3; i++)
		cin >> pp[i].x >> pp[i].y;
	string cmd;
	cin >> cmd;
	switch(cmd[0]) {
	case 'I':
		i(pp);
		break;
	case 'O':
		o(pp);
		break;
	}
	return 0;
}
