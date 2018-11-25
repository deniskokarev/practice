#include <iostream>
#include <algorithm>
/* CodeForces CF830C problem */
using namespace std;

bool fit(const int *aa, int n, int64_t d, int64_t c) {
	int64_t tot = 0;
	for (int i=0; i<n; i++)
		tot += (aa[i]+d-1)/d;
	return (c >= tot*d);
}

constexpr int MXV = 1e9+1;
constexpr int MXF = 32000; // ~>sqrt(MXV)

int ff[2*MXF*100+2]; // all factors

int main(int argc, char **argv) {
	int n;
	int64_t k;
	cin >> n >> k;
	int64_t sm = 0;
	int aa[n];
	//int ff[2*MXF*n+2]; // all factors
	int ff_sz = 0;
	for (auto &a:aa) {
		cin >> a;
		sm += a;
		for (int f=1; f*f <= a; f++) {
			if (a % f == 0) {
				ff[ff_sz++] = f;
				ff[ff_sz++] = a/f;
			}
		}
	}
	sort(ff, ff+ff_sz);
	ff_sz = int(unique(ff, ff+ff_sz)-ff);
	ff[ff_sz++] = MXV;
	int64_t c = k+sm;
	int d = -1;
	// solution will lie between factors
	for (int i=ff_sz-2; i >= 0; i--) {
		int f=ff[i], t=ff[i+1];
		while (f<t) {
			int m = f+(t-f)/2;
			if (fit(aa, n, m, c))
				f = m+1;
			else
				t = m;
		}
		if (f > ff[i]) {
			d = f-1;
			break;
		}
	}
	cout << d << endl;
	return 0;
}
