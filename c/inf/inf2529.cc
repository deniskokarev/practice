#include <iostream>
#include <limits.h>
/* ROI 2010 A problem */
using namespace std;

int64_t isqrt(int64_t s) {
	int64_t f=1, t=INT_MAX;
	while (f<t) {
		int64_t m = f+(t-f)/2;
		if (m*m <= s)
			f = m+1;
		else
			t = m;
	}
	return f-1;
}

int main(int argc, char **argv) {
	uint64_t n;
	cin >> n;
	int64_t a = isqrt(n/6);
	// try +1
	int64_t s1 = a*a*2+a*(a+1)*4;
	// try +2
	int64_t s2 = (a+1)*(a+1)*2+a*(a+1)*4;
	if (s2 <= n) {
		cout << (a+1)*(a+1)*a << endl;
		cout << (a+1) << ' ' << (a+1) << ' ' << a << endl;
	} else if (s1 <= n) {
		cout << (a+1)*a*a << endl;
		cout << (a+1) << ' ' << a << ' ' << a << endl;
	} else {
		cout << a*a*a << endl;
		cout << a << ' ' << a << ' ' << a << endl;
	}
	return 0;
}
