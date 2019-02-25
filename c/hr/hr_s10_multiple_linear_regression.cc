#include <iostream>
#include <iomanip>
/* https://www.hackerrank.com/challenges/s10-multiple-linear-regression */
using namespace std;

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
	Mat mat_minor(int r, int c) const {
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
				Mat mr = mat_minor(r, c);
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
	Mat inv() const {
		N d = det();
		assert(d != 0 && "if det == 0, we cannot find inverse");
		Mat res = adj();
		res *= 1/d;
		return res;
	}
	Mat transpose() const {
		Mat a(cols, rows);
		for (int i=0; i<rows; i++)
			for (int j=0; j<cols; j++)
				a[j][i] = operator[](i)[j];
		return a;
	}
};

int main(int argc, char **argv) {
	int m, n;
	cin >> m >> n;
	Mat<double> F(n, m+1);
	Mat<double> Y(n, 1);
	for (int i=0; i<n; i++) {
		F[i][0] = 1;
		for (int j=1; j<=m; j++)
			cin >> F[i][j];
		cin >> Y[i][0];
	}
	Mat<double> FT = F.transpose();
	Mat<double> B = FT.mul(F).inv().mul(FT).mul(Y);
	cout << setprecision(2) << fixed;
	int q;
	cin >> q;
	while (q--) {
		Mat<double> X(1,m+1);
		X[0][0] = 1;
		for (int i=1; i<=m; i++)
			cin >> X[0][i];
		Mat<double> R = X.mul(B);
		cout << R[0][0] << endl;
	}
	return 0;
}
