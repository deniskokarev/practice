#include <iostream>
#include <cmath>
#include <algorithm>

/* CodeForces CF812C problem */
using namespace std;

static int64_t sum(int64_t aa[], int64_t n, int64_t k) {
	int64_t as[n];
	for (int64_t i=0; i<n; i++)
		as[i] = aa[i]+(i+1)*k;
	make_heap(as, as+n, greater<int64_t>());
	int64_t smx = 0;
	for (int64_t i=0; i<k; i++) {
		smx += as[0];
		pop_heap(as, as+n, greater<int64_t>());
		n--;
		if (n<=0)
			break;
	}
	return smx;
}

int main(int argc, char **argv) {
	int64_t n, s;
	cin >> n >> s;
	int64_t aa[n];
	for (auto &a:aa)
		cin >> a;
	int64_t kub = min((int64_t)sqrt(s*4), n+1);
	int64_t klb = 0;
	int64_t k = 0;
	int64_t smx;
	while (klb < kub) {
		k = (kub+klb)/2;
		smx = sum(aa, n, k);
		if (smx <= s)
			klb = k+1;
		else
			kub = k;
	}
	if (sum(aa, n, k) > s)
		k--;
	smx = sum(aa, n, k);
	cout << k << " " << smx << endl;
	return 0;
}
