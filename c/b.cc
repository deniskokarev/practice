#include <iostream>
#include <bitset>
#include <algorithm>

/* CodeForces CF916B problem */
using namespace std;

bool scatter(int dnn[36], int ndnn[36], int hi, int cnt) {
	if (dnn[hi] > cnt) {
		ndnn[hi] = dnn[hi]-cnt;
	} else {
	}
	return false;
}

int flatten_and_print_answer(uint64_t b, int k, int o, int l, int an) {
	cout << "Yes" << endl;
	int dnn[36] = {0}; // number of powers of 2
	dnn[an+18] = l;
	dnn[18] = o;
	int p = 0;
	while (b>0) {
		if (b & 1)
			dnn[p+18]++;
		b >>= 1;
		p++;
	}
	int ndnn[36];
	while (1) {
		for (int i=35; i>=0; i--) {
			if (dnn[i] > 0 && !scatter(dnn, ndnn, i, 1))
				goto done;
			else
				copy(ndnn, ndnn+36, dnn);
		}
	}
 done:
	for (int i=35; i>=0; i--)
		for (int j=0; j<dnn[i]; j++)
			cout << i-18 << ' ';
	cout << endl;
	return 0;
}

int main(int argc, char **argv) {
	uint64_t n;
	int k;
	cin >> n >> k;
	for (int an=0,l=1; l<=k; l<<=1,an--) { // l - len of neg section summarizing altogether to 1
		for (int o=0; o<=k-l && n >= o+1; o++) { // o - len of zeros section summarizing to o
			bitset<64> bb(n-1-o);
			if (bb.count() == k-l-o)
				return flatten_and_print_answer(n-1-o, k, o, l, an);
		}
	}
	cout << "No" << endl;
	return 0;
}
