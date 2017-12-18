/* ACMP 1433 */
#include <iostream>
#include <cassert>

using namespace std;

// precompute floor(log2) values [1..mx] inclusive
// ll buf must have mx+1 free space
void fill_floor_log2(int mx, unsigned char *ll) {
	ll[0] = 255; // undefined value
	ll[1] = 0;
	int i = 2;
	int l2, p2;
	for (l2=1,p2=2; i+p2<=mx; l2++,p2<<=1) {
		int j;
		for (j=0; j<p2; j++)
			ll[i+j] = l2;
		i += j;
	}
	while (i<=mx)
		ll[i++] = l2;
}

// precompute ceil(log2) values [1..mx] inclusive
// ll buf must have mx+1 free space
void fill_ceil_log2(int mx, unsigned char *ll) {
	fill_floor_log2(mx, ll);
	for (int i=1; i<=mx; i++)
		ll[i]++;
	for (int p2=1; p2<=mx; p2<<=1)
		ll[p2]--;
}

constexpr unsigned mod31_mask = (1ULL<<31)-1;
constexpr unsigned pmod = (1ULL<<31)-1; // prime modulo

unsigned inline next_r(unsigned r) {
	return (r*1103515245+12345) & mod31_mask;
}

int main(int argc, char **argv) {
	unsigned n, q;
	unsigned r;
	cin >> n >> q >> r;
	assert((n&(n-1))==0 && "n must be power of 2");
	unsigned char floor_log2[n+2];
	unsigned char ceil_log2[n+2];
	fill_floor_log2(n+1, floor_log2);
	fill_ceil_log2(n+1, ceil_log2);
	int l2 = ceil_log2[n+1]+1;
	unsigned modn = n-1;
	unsigned aa[l2][n+1];
	unsigned r15 = r >> 16;
	aa[0][0] = r15;
	for (int i=1; i<=n; i++) {
		r = next_r(r);
		r15 = r >> 16;
		aa[0][i] = r15;
	}
	for (int i=1,p2=1; i<l2; i++,p2<<=1)
		for (int j=0; j<n; j++)
			if (j+p2<n)
				aa[i][j] = min(aa[i-1][j], aa[i-1][j+p2]);
			else
				aa[i][j] = aa[i-1][j];
	uint64_t sum = 0;
	for (int i=1; i<2*q; i++,i++) {
		r = next_r(r);
		r15 = r >> 16;
		unsigned b1 = (r15&modn)+1;
		r = next_r(r);
		r15 = r >> 16;
		unsigned b2 = (r15&modn)+1;
		unsigned l = min(b1, b2);
		unsigned r = max(b1, b2);
		int len = r-l+1;
		int fl2 = floor_log2[len];
		int p2 = 1<<fl2;
		int mnl = aa[fl2][l];
		int mnr = aa[fl2][r-p2+1];
		int mn = min(mnl, mnr);
		sum += mn;
	}
	cout << sum % pmod << endl;
	return 0;
}
