#include <iostream>
/* CodeForces CF830C problem */
using namespace std;

bool fit(const int64_t *aa, int n, int64_t d, int64_t c) {
	int64_t tot = 0;
	for (int i=0; i<n; i++)
		tot += (aa[i]+d-1)/d;
	return (c >= tot*d);
}

int main(int argc, char **argv) {
	int64_t n, k;
	cin >> n >> k;
	int64_t sm = 0;
	int64_t aa[n];
	for (auto &a:aa) {
		cin >> a;
		sm += a;
	}
	int64_t c = k+sm;
	int64_t f=100000, t=1e9+1;
	while (f<t) {
		int64_t m = f+(t-f)/2;
		if (fit(aa, n, m, c))
			f = m+1;
		else
			t = m;
	}
	// below sqrt(1e9) need to go sequentially 
	int64_t d = f-1;
	if (!fit(aa, n, d, c)) {
		while (d>0) {
			int64_t tot = 0;
			for (auto a:aa)
				tot += (a+d-1)/d;
			if (fit(aa, n, d, c))
				break;
			d--;
		}
	}
	cout << d << endl;
	return 0;
}
