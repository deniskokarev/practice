#include <cstdio>
#include <cinttypes>
#include <algorithm>
/* https://www.hackerrank.com/challenges/s10-weighted-mean */
using namespace std;

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	uint64_t smwx = 0;
	uint64_t smw = 0;
	int xx[n];
	for (auto &x:xx)
		scanf("%d", &x);
	for (int i=0; i<n; i++) {
		int64_t w;
		scanf("%" PRId64, &w);
		smwx += xx[i] * w;
		smw += w;
	}
	int wm10 = (smwx*20+smw)/smw/2;
	printf("%d.%d\n", wm10/10, wm10%10);
	return 0;
}
