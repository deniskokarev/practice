#include <iostream>
#include <algorithm>
#include <cassert>
/* CodeForces CF1088D problem */
using namespace std;

constexpr int BITS = 4;

int ask(int c, int d) {
	cout << "? " << c << " " << d << endl;
	int resp;
	cin >> resp;
	return resp;
}

void do_eq(int *abit, int *bbit, int pa, int pb) {
	for (int i=0; i<BITS; i++) {
		if (abit[i] < 0) {
			if (ask(pa | (1<<i), pb) == -1) {
				abit[i] = 1;
				bbit[i] = 1;
			} else {
				abit[i] = 0;
				bbit[i] = 0;
			}
		}
	}
}

void do_gt(int *abit, int *bbit, int pa, int pb, int n);

void do_lt(int *abit, int *bbit, int pa, int pb, int n) {
	for (int i=n; i>=0; i--) {
		if (ask(pa | (1<<i), pb | (1<<i)) == 1) {
			abit[i] = 0;
			bbit[i] = 1;
			pa |= 1<<i;
			return do_gt(abit, bbit, pa, pb, i-1);
		}
	}
	return do_eq(abit, bbit, pa, pb);
}

void do_gt(int *abit, int *bbit, int pa, int pb, int n) {
	for (int i=n; i>=0; i--) {
		if (ask(pa | (1<<i), pb | (1<<i)) == -1) {
			abit[i] = 1;
			bbit[i] = 0;
			pa |= 1<<i;
			return do_lt(abit, bbit, pa, pb, i-1);
		}
	}
	return do_eq(abit, bbit, pa, pb);
}

int val(int *b) {
	int res = 0;
	for (int i=0,p2=1; i<BITS; i++,p2*=2)
		res += p2*b[i];
	return res;
}

int main(int argc, char **argv) {
	int abit[BITS], bbit[BITS];
	fill(abit, abit+BITS, -1);
	fill(bbit, bbit+BITS, -1);
	int ap = 0, bp = 0;
	switch (ask(ap, bp)) {
	case -1:
		do_lt(abit, bbit, ap, bp, BITS);
		break;
	case 1:
		do_gt(abit, bbit, ap, bp, BITS);
		break;
	default:
		do_eq(abit, bbit, ap, bp);
	}
	cout << "! " << val(abit) << " " << val(bbit) << endl;
	return 0;
}
