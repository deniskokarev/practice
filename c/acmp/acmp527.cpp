#include <iostream>
/* ACMP 527 */
using namespace std;

// possible values of a,b in the form of range and step
struct R {
	uint64_t af, at, as;
	uint64_t bf, bt, bs;
};

// rr size must be > 64
int build_list(uint64_t a, uint64_t b, R *rr) {
	int sz = 0;
	rr[sz++] = {a, a, 1, b, b, 1};
	while (b>0) {
		rr[sz++] = {a%b, a, b, b, b, 1};
		auto ob = b;
		b = a%b;
		a = ob;
	}
	return sz;
}

bool can_match(uint64_t a, uint64_t b, uint64_t c, uint64_t d) {
	R rr[128];
	int sz = build_list(a, b, rr);
	for (int i=0; i<sz; i++) {
		if (c>=rr[i].af && c<=rr[i].at && (c-rr[i].af)%rr[i].as == 0 &&
			d>=rr[i].bf && d<=rr[i].bt && (d-rr[i].bf)%rr[i].bs == 0)
			return true;
	}
	return false;
}

int main(int argc, char **argv) {
	int k;
	cin >> k;
	while (k--) {
		uint64_t a, b, c, d;
		cin >> a >> b >> c >> d;
		cout << (can_match(a, b, c, d)?"YES":"NO") << endl;
	}
	return 0;
}
