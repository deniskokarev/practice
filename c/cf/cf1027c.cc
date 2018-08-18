#include <iostream>
#include <vector>
#include <algorithm>
/* CodeForces CF1027C problem */
using namespace std;

struct Q {
	uint64_t n, d;
	Q(uint64_t _n, uint64_t _d):n(_n),d(_d){}
	bool operator <(const Q &b) {
		return n*b.d < b.n*d;
	}
};

int main(int argc, char **argv) {
	int t;
	cin >> t;
	vector<int> cnt(10000+1);
	vector<int> ll(1000000+1);
	vector<int> ss(1000000+1);
	vector<int> rr(1000000+1);
	while (t--) {
		int n;
		cin >> n;
		for (int i=0; i<n; i++) {
			cin >> ll[i];
			cnt[ll[i]]++;
		}
		int ssz = 0;
		int rsz = 0;
		for (int i=0; i<n; i++) {
			if (cnt[ll[i]] > 3) {
				ss[ssz++] = ll[i];
			} else if (cnt[ll[i]] > 1) {
				rr[rsz++] = ll[i];
			}
			cnt[ll[i]] = 0;
		}
		sort(ss.begin(), ss.begin()+ssz);
		sort(rr.begin(), rr.begin()+rsz);
		// select best req from ss sticks
		if (ssz > 0) {
			cout << ss[ssz-1] << ' ' << ss[ssz-1] << ' ' << ss[ssz-1] << ' ' << ss[ssz-1] << '\n';
		} else {
			// no squares - find the best rect
			Q mn_q(1e9, 1);
			int mn_i, mn_j;
			for (int i=rsz-1; i>0; i--) {
				uint64_t n = rr[i]*2 + rr[i-1]*2;
				n *= n;
				uint64_t s = rr[i];
				s *= rr[i-1];
				Q q(n, s);
				if (q < mn_q) {
					mn_q = q;
					mn_i = i;
					mn_j = i-1;
				}
			}
			cout << rr[mn_i] << ' ' << rr[mn_i] << ' ' << rr[mn_j] << ' ' << rr[mn_j] << '\n';
		}
	}
	return 0;
}
