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

constexpr unsigned mod31_mask = (1ULL<<31)-1;

unsigned inline next_r(unsigned r) {
	return (r*1103515245+12345) & mod31_mask;
}

int main(int argc, char **argv) {
	unsigned n, q;
	unsigned r;
	cin >> n >> q >> r;
	assert((n&(n-1))==0 && "n must be power of 2");
	unsigned char log2[n+1];
	fill_floor_log2(n, log2);
	int l2 = log2[n]+1; // we know it's ceil_log2
	unsigned modn = n-1;
	unsigned aa[l2][n]; // multilevel minimums
	unsigned r15;
	// fill 0-level with R15 sequence
	for (int i=0; i<n; i++) {
		r = next_r(r);
		r15 = r >> 16;
		aa[0][i] = r15;
	}
	// populate min for each 2^i segment
	for (int i=1,p2=1; i<l2; i++,p2<<=1)
		for (int j=0; j<n; j++)
			if (j+p2<n)
				aa[i][j] = min(aa[i-1][j], aa[i-1][j+p2]);
			else
				aa[i][j] = aa[i-1][j];
	// continue R15 sequence and each time find min on [l,r] in O(1)
	unsigned sum = 0;
	for (int i=1; i<2*q; i++,i++) {
		r = next_r(r);
		r15 = r >> 16;
		unsigned b1 = (r15&modn)+1;
		r = next_r(r);
		r15 = r >> 16;
		unsigned b2 = (r15&modn)+1;
		unsigned l = min(b1, b2);
		unsigned r = max(b1, b2);
		l--, r--;
		int len = r-l+1;
		int fl2 = log2[len];
		int p2 = 1<<fl2;
		unsigned mnl = aa[fl2][l];
		unsigned mnr = aa[fl2][r-p2+1];
		unsigned mn = min(mnl, mnr);
		sum += mn;
	}
	cout << (sum & mod31_mask) << endl;
	return 0;
}
