/* ACMP 335 */
#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

constexpr uint64_t mod = 1e9+9;

#define dim(X)	(sizeof(X)/sizeof(X[0]))

int main(int argc, char **argv) {
	int n;
	cin >> n;
	bool pp[1000];
	fill(pp, pp+dim(pp), true);
	pp[0] = pp[1] = false;
	for (int i=2; i<32; i++)
		for (int j=i+i; j<1000; j+=i)
			pp[j] = false;
	for (int i=0; i<100; i++)
		pp[i] = false;
	uint64_t hh[2][100];
	fill(hh[0], hh[0]+dim(hh[0]), 0);
	for (int i=0; i<1000; i++)
		if (pp[i])
			hh[0][(i/10)%100]++;
	for (int k=1; k<=n-3; k++) {
		fill(hh[k&1], hh[k&1]+dim(hh[0]), 0);
		for (int i=1; i<10; i++)
			for (int j=0; j<100; j++)
				if (pp[i*100+j])
					hh[k&1][i*10+j/10] += hh[(k+1)&1][j];
		for (auto &h:hh[k&1])
			h %= mod;
	}
	uint64_t ans = accumulate(hh[(n+1)&1], hh[(n+1)&1]+dim(hh[0]), 0ULL);
	cout << ans % mod << endl;
	return 0;
}
