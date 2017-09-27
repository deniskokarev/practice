/* ACMP 334 */
#include <algorithm>
#include <limits.h>
#include <stdio.h>

using namespace std;

int main(int argc, char **argv) {
	uint64_t n;
	scanf("%lld", &n);
	uint64_t tt[n+1];
	tt[0] = 0;
	for (int i=1; i<=n; i++) {
		int h, m, s;
		scanf("%d:%d:%d", &h, &m, &s);
		tt[i] = ((h*60)+m)*60+s;
	}
	sort(tt, tt+n);
	uint64_t ss[n+1];
	ss[0] = 0;
	for (int i=1; i<=n; i++)
		ss[i] = ss[i-1]+tt[i];
	uint64_t mn = ULLONG_MAX;
	int mnt = -1;
	for (int t=0; t<12*60*60; t++) {
		uint64_t *ip = upper_bound(tt, tt+n+1, t);
		uint64_t i = ip-tt;
		uint64_t s = (i-1)*t - ss[i-1];
		s += (n+1-i)*t;
		s += (n+1-i)*12*60*60 - (ss[n]-ss[i-1]);
		if (s < mn) {
			fprintf(stderr, "%02d:%02d:%02d   %lld\n", t/3600, (t/60)%60, t%60, s);
			mnt = t;
			mn = s;
		}
	}
	printf("%02d:%02d:%02d\n", mnt/3600, (mnt/60)%60, mnt%60);
	return 0;
}
