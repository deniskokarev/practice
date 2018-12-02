#include <iostream>
#include <algorithm>
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
	const int D = 100;
	int choose = 1;
	for (int i=1; i<=3; i++) {
		choose *= D + 3 - i;
		choose /= i;
	}
	A ans[choose];
	int ai = 0;
	for (int i=0; i<D; i++)
		for (int j=i; j<D; j++)
			for (int k=j; k<D; k++)
				ans[ai++] = A {a+i, a+j, a+k};
	sort(ans, ans+choose, [](const A &a, const A &b){return a.volume() > b.volume();});
	for (auto &a:ans) {
		if (a.area() <= n) {
			cout << a.volume() << endl;
			cout << a.a << ' ' << a.b << ' ' << a.c << endl;
			break;
		}
	}
	return 0;
}
