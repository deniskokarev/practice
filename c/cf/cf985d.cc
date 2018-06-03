#include <iostream>
/* CodeForces CF985D problem */
using namespace std;

// find base width of the pyramid centered at c
// with the side hieght <= H
// and total volume no less than n
int64_t width(int64_t c, int64_t n, int64_t H, int64_t &s) {
	if (c>=0) {
		int64_t h = H+c;
		s = h*h - H*(H-1)/2;
		if (s >= n)
			return 2*h-H;
	} else {
		if (c >= -H) {
			int64_t h = H+c;
			if (h>0) {
				s = h*(h+1)/2;
				if (s >= n)
					return h;
			}
		}
	}
	return -1;
}

int main(int argc, char **argv) {
	int64_t n, H;
	cin >> n >> H;
	// cap unreasonable H values to prevent overflow
	if (H > INT_MAX)
		H = INT_MAX;
	int64_t s; // volume
	// upper bound search of pyramid center
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
	// check if it is possible to shave off right slope without moving center of the pyramid
	if (cf > 0 && n <= s-(w-cf))
		w--;
	cout <<  w << endl;
	return 0;
}
