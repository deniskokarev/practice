#include <iostream>
/* CodeForces CF830C problem */
using namespace std;

int64_t rem(int64_t *aa, int n, int64_t d) {
	int64_t r = 0;
	for (int i=0; i<n; i++)
		r += (aa[i]+d-1)/d;
	return d*r;
}

int main(int argc, char **argv) {
	int n;
	int64_t k;
	int64_t sum = 0;
	cin >> n >> k;
	int64_t aa[n];
	for (auto &a:aa) {
		cin >> a;
		sum += a;
	}
#if 0
	int64_t pv = -1;
	for (int d=1; d<100; d++) {
		int64_t r = rem(aa, n, d); 
		//cerr << r << endl;
		if (r<pv)
			cerr << "wow!: " << d-1 << "->" << pv << ", " << d << "->" << r << endl;
		pv = r;
	}
#else	
	int64_t e = 1000000000LL+1; // 10^9
	int64_t b = 1;
	int64_t m = b;
	while (b<e) {
		m = b+(e-b)/2;
		if (k >= rem(aa, n, m)-sum) {
			b = m+1;
		} else {
			e = m;
		}
	}
	if (k >= rem(aa, n, m)-sum)
		cout << m << endl;
	else
		cout << m-1 << endl;
#endif
	return 0;
}
