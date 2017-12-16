/* ACMP 1432 */
#include <iostream>

using namespace std;

constexpr unsigned b31 = 1ULL<<31;
constexpr unsigned mod31 = b31-1;

int main(int argc, char **argv) {
	unsigned pn, q;
	uint64_t r;
	cin >> pn >> q >> r;
	unsigned n = 1<<pn;
	unsigned modn = pn-1;
	unsigned aa[n+1];
	unsigned r15[n+1];
	aa[0] = r;
	r15[0] = r >> 16;
	for (int i=1; i<=n; i++) {
		r = (r*1103515245+12345) & mod31;
		unsigned rdiv = r >> 16;
		r15[i] = rdiv;
		aa[i] = aa[i-1] + rdiv; // don't bother with mod31
		//cerr << r << " " << endl;
		//cerr << r15[i] << " ";
	}
	unsigned sum = 0;
	for (int i=1; i<2*q; i++,i++) {
		unsigned b1 = (r15[pn+i]&modn)+1;
		unsigned b2 = (r15[pn+i+1]&modn)+1;
		unsigned l = min(b1, b2);
		unsigned r = max(b1, b2);
		//cerr << "l: " << l << " r: " << r << endl;
		unsigned s = b31 + aa[r] - aa[l-1];
		//cerr << s << endl;
		sum += s;
	}
	cout << (sum & mod31) << endl;
	return 0;
}
