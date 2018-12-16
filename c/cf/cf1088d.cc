#include <iostream>
#include <algorithm>
#include <cassert>
/* CodeForces CF1088D problem */
using namespace std;

constexpr int BITS = 29;

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

void do_continue(int *abit, int *bbit, int pa, int pb, int n);

void do_lt(int *abit, int *bbit, int pa, int pb, int n) {
	for (int i=n; i>=0; i--) {
		if (ask(pa | (1<<i), pb | (1<<i)) == 1) {
			abit[i] = 0;
			bbit[i] = 1;
			pb |= 1<<i;
			return do_continue(abit, bbit, pa, pb, i-1);
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
			return do_continue(abit, bbit, pa, pb, i-1);
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

void do_continue(int *abit, int *bbit, int pa, int pb, int n) {
	if (n>=0) {
		switch (ask(pa, pb)) {
		case -1:
			return do_lt(abit, bbit, pa, pb, n);
		case 1:
			return do_gt(abit, bbit, pa, pb, n);
		default:
			return do_eq(abit, bbit, pa, pb);
		}
	}
	return do_eq(abit, bbit, pa, pb);
}

int main(int argc, char **argv) {
	int abit[BITS], bbit[BITS];
	fill(abit, abit+BITS, -1);
	fill(bbit, bbit+BITS, -1);
	do_continue(abit, bbit, 0, 0, BITS);
	cout << "! " << val(abit) << " " << val(bbit) << endl;
	return 0;
}
