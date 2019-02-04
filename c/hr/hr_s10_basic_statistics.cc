#include <cstdio>
#include <cinttypes>
#include <algorithm>
/* Hackerrank stats https://www.hackerrank.com/challenges/s10-basic-statistics */
using namespace std;

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	uint64_t sm = 0;
	int aa[n];
	for (int i=0; i<n; i++) {
		scanf("%d", &aa[i]);
		sm += aa[i];
	}
	sort(aa, aa+n);
	int i=0;
	int mode = aa[0], mxcnt = 1;
	while (i<n) {
		int cnt = 1;
		i++;
		while (i<n && aa[i-1]==aa[i])
			cnt++, i++;
		if (cnt > mxcnt) {
			mode = aa[i-1];
			mxcnt = cnt;
		}
	}
	int median10;
	if (n&1)
		median10 = aa[n/2]*10;
	else
		median10 = (aa[n/2-1]+aa[n/2])*5;
	int ave10 = (sm*20+n)/n/2;
	printf("%d.%d\n%d.%d\n%d\n", ave10/10, ave10%10,  median10/10, median10%10, mode);
	return 0;
}
