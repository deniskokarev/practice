/* ACMP 936 */
#include <iostream>

using namespace std;

struct V {
	int64_t x, y;
	void operator -=(const V &v) {
		x -= v.x;
		y -= v.y;
	}
	int64_t cross(const V &b) const {
		return x*b.y-b.x*y;
	}	
};

int main(int argc, char **argv) {
	V c;
	double r;
	cin >> c.x >> c.y >> r;
	if (r>2001)
		r = 2001; // prevent int overflow
	int r2 = r*r;
	int n;
	cin >> n;
	V pp[n];
	int np = 0;
	for (int i=0; i<n; i++) {
		V &p = pp[np];
		cin >> p.x >> p.y;
		p -= c;
		if (p.x*p.x + p.y*p.y <= r2)
			np++;
	}
	int mxcnt = 0;
	for (int i=0; i<np; i++) {
		int cnt = 0;
		for (int j=0; j<np; j++)
			if (pp[i].cross(pp[j]) >= 0)
				cnt++;
		mxcnt = max(mxcnt, cnt);
	}
	cout << mxcnt << endl;
	return 0;
}
