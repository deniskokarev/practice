/* ACMP 1432 */
#include <iostream>
#include <cassert>

using namespace std;

constexpr unsigned mod31 = (1ULL<<31)-1;

int main(int argc, char **argv) {
	unsigned n, q;
	uint64_t r;
	cin >> n >> q >> r;
	assert((n&(n-1))==0 && "n must be power of 2");
	unsigned modn = n-1;
	unsigned *aa = new unsigned[n+1];
	unsigned *r15 = new unsigned[n+1];
	aa[0] = r;
	unsigned rdiv = r >> 16;
	r15[0] = rdiv;
	for (int i=1; i<=n; i++) {
		r = (r*1103515245+12345) & mod31;
		rdiv = r >> 16;
		r15[i] = rdiv;
		aa[i] = aa[i-1] + rdiv; // don't bother with mod31
		//cerr << r << " ";
		//cerr << r15[i] << " ";
	}
	unsigned sum = 0;
	for (int i=1; i<2*q; i++,i++) {
		r = (r*1103515245+12345) & mod31;
		rdiv = r >> 16;
		unsigned b1 = (rdiv&modn)+1;
		r = (r*1103515245+12345) & mod31;
		rdiv = r >> 16;
		unsigned b2 = (rdiv&modn)+1;
		unsigned l = min(b1, b2);
		unsigned r = max(b1, b2);
		//cerr << "l: " << l << " r: " << r << endl;
		unsigned s = aa[r] - aa[l-1];
		//cerr << s << endl;
		sum += s;
	}
	delete[] aa;
	delete[] r15;
	cout << (sum & mod31) << endl;
	return 0;
}
