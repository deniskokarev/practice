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

struct A {
	int64_t a, b, c;
	int64_t area() const {
		return a*b*2 + b*c*2 + c*a*2;
	}
	int64_t volume() const {
		return a*b*c;
	}
};

int main(int argc, char **argv) {
	uint64_t n;
	cin >> n;
	int64_t a = isqrt(n/6);
	A ans[4] = {
		A {a+1, a+1, a+1},
		A {a+1, a+1, a},
		A {a+1, a, a},
		A {a, a, a}
	};
	for (auto &a:ans) {
		if (a.area()<=n) {
			cout << a.volume() << endl;
			cout << a.a << ' ' << a.b << ' ' << a.c << endl;
			break;
		}
	}
	return 0;
}
