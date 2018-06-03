#include <iostream>
/* CodeForces CF985D problem */
using namespace std;

int64_t width(int64_t c, int64_t n, int64_t H, int64_t &s) {
	if (c>=0) {
		int64_t h = H+c;
		s = h*h - H*(H-1)/2;
		if (s >= n) {
			cerr << "c=" << c << " s=" << s << " w=" << 2*h-H << endl;
			return 2*h-H;
		}
	} else {
		if (c >= -H) {
			int64_t h = H+c;
			if (h>0) {
				s = h*(h+1)/2;
				if (s >= n) {
					cerr << "c=" << c << " s=" << s << " w=" << h << endl;
					return h;
				}
			}
		}
	}
	return -1;
}

int main(int argc, char **argv) {
	int64_t n, H;
	cin >> n >> H;
	if (H > INT_MAX)
		H = INT_MAX;
	int64_t s;
	// upper bound search of pile center
	int64_t cf=INT_MIN, ct=INT_MAX;
	while (cf < ct) {
		int64_t cm = cf+(ct-cf)/2;
		int64_t w = width(cm, n, H, s);
		if (w == -1)
			cf = cm+1;
		else
			ct = cm;
	}
	int64_t w = width(cf, n, H, s);
	if (cf > 0 && n <= s-(w-cf))
		w--;
	cout <<  w << endl;
	return 0;
}
