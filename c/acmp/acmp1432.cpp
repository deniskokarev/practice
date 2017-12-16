/* ACMP 1432 */
#include <iostream>
#include <cassert>

using namespace std;

constexpr unsigned mod31 = (1ULL<<31)-1;

unsigned inline next_r(unsigned r) {
	return (r*1103515245+12345) & mod31;
}

int main(int argc, char **argv) {
	unsigned n, q;
	unsigned r;
	cin >> n >> q >> r;
	assert((n&(n-1))==0 && "n must be power of 2");
	unsigned modn = n-1;
	unsigned aa[n+1];
	aa[0] = r;
	unsigned r15 = r >> 16;
	for (int i=1; i<=n; i++) {
		r = next_r(r);
		r15 = r >> 16;
		aa[i] = aa[i-1] + r15; // don't bother with mod31
		//cerr << r << " ";
		//cerr << r15 << " ";
	}
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
		//cerr << "l: " << l << " r: " << r << endl;
		unsigned s = aa[r] - aa[l-1];
		//cerr << s << endl;
		sum += s;
	}
	cout << (sum & mod31) << endl;
	return 0;
}
