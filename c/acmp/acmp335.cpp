/* ACMP 335 */
#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

constexpr uint64_t mod = 1e9+9;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<bool> pp(1000, true);
	pp[0] = pp[1] = false;
	for (int i=2; i<32; i++)
		for (int j=i+i; j<1000; j+=i)
			pp[j] = false;
	for (int i=0; i<100; i++)
		pp[i] = false;
	vector<vector<uint64_t>> hh(2, vector<uint64_t>(100));
	for (int i=0; i<1000; i++)
		if (pp[i])
			hh[0][(i/10)%100]++;
	for (int k=1; k<=n-3; k++) {
		fill(hh[k&1].begin(), hh[k&1].end(), 0);
		for (int i=1; i<10; i++)
			for (int j=0; j<100; j++)
				if (pp[i*100+j])
					hh[k&1][i*10+j/10] += hh[(k+1)&1][j];
		for (auto &h:hh[k&1])
			h %= mod;
	}
	uint64_t ans = accumulate(hh[(n+1)&1].begin(), hh[(n+1)&1].end(), 0ULL);
	cout << ans << endl;
	return 0;
}
