#include <stdio.h>
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

int cnt[10000+1]; // max len is guaranteed to be <=10^4
int ll[1000000+1];
int ss[1000000+1]; // squares
int rr[1000000+1]; // rectangles

int main(int argc, char **argv) {
	int t;
	scanf("%d", &t);
	while (t--) {
		int n;
		scanf("%d", &n);
		for (int i=0; i<n; i++) {
			scanf("%d", &ll[i]);
			cnt[ll[i]]++;
		}
		int ssz = 0;
		int rsz = 0;
		for (int i=0; i<n; i++) {
			if (cnt[ll[i]] >= 4) {
				ss[ssz++] = ll[i];
			} else if (cnt[ll[i]] >= 2) {
				rr[rsz++] = ll[i];
			}
			cnt[ll[i]] = 0;
		}
		if (ssz > 0) {
			// select any square
			printf("%d %d %d %d\n", ss[0], ss[0], ss[0], ss[0]);
		} else {
			// no squares - find the best rect (it's guaranteed to exist)
			Q mn_q(1e9, 1);
			int mn_i;
			sort(rr, rr+rsz);
			for (int i=rsz-1; i>0; i--) {
				uint64_t n = rr[i]*2 + rr[i-1]*2;
				n *= n;
				uint64_t s = rr[i];
				s *= rr[i-1];
				Q q(n, s);
				if (q < mn_q) {
					mn_q = q;
					mn_i = i;
				}
			}
			printf("%d %d %d %d\n", rr[mn_i], rr[mn_i], rr[mn_i-1], rr[mn_i-1]);
		}
	}
	return 0;
}
