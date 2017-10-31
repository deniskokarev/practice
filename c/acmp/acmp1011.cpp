/* ACMP 1011 */

/*
 * Our generic Matrix stuff
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
#include <cmath>

using namespace std;

struct P : public Mat<double> {
	double &x, &y;
	P():Mat(1,2),x(vv[0]),y(vv[1]) {}
	P(double _x, double _y):P() {
		x = _x;
		y = _y;
	}
	void operator=(const P &b) {
		x = b.x;
		y = b.y;
	}
	P operator-(const P &b) const {
		P res(x-b.x, y-b.y);
		return res;
	}
	double cross(const P &b) const {
		return x*b.y - y*b.x;
	}
};

void i(const P pp[3]) {
	P o;
	double ar2 = 0; // average r square
	for (double e = 10.0; e >= .00001; e/=10) {
		double mnerr = 1e10;
		P mno;
		for (int ny=-10; ny<=10; ny++) {
			for (int nx=-10; nx<=10; nx++) {
				P oo = o - P(nx*e, ny*e);
				double rr2[3];
				ar2 = 0;
				for (int i=0; i<3; i++) {
					int j=(i+1)%3;
					double cr = (pp[i]-oo).cross(pp[j]-oo);
					rr2[i] = cr*cr/(pp[j]-pp[i]).len_sq();
					ar2 += rr2[i];
				}
				ar2 /= 3.0;
				double err = 0;
				for (auto r2:rr2)
					err += fabs(r2-ar2);
				if (mnerr > err) {
					mno = oo;
					mnerr = err;
				}
			}
		}
		o = mno;
	}
	cout << o.x << " " << o.y << " " << sqrt(ar2) << endl;
}


// working of the fact that dot product between vectors representing the side
// and the vector from center to the middle of side must be == 0
void o(const P pp[3]) {
	Mat<double> mm(2,2);
	Mat<double> cc(2,1);
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
			P o(res[0][0], res[1][0]);
			P rv = pp[i];
			rv -= o;
			cout << o.x << " " << o.y << " " << sqrt(rv.len_sq()) << endl;
			break;
		}
	}
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
