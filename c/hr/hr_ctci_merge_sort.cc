#include <cstdio>
#include <cstring>
#include <cinttypes>
#include <memory>
/* Hackerrank https://www.hackerrank.com/challenges/ctci-merge-sort */

void fw_inc(int *fw, int fw_sz, int x, int d) {
	for (int i=x; i<fw_sz; i|=i+1)
		fw[i] += d;;
}

int fw_sum(const int *fw, int x) {
	int s = 0;
	for (int i=x; i>=0; i=(i&(i+1))-1)
		s += fw[i];
	return s;
}

constexpr int MXA = 1e7+1;

int main(int argc, char **argv) {
	int q;
	scanf("%d", &q);
	while (q--) {
		int n;
		scanf("%d", &n);
		std::unique_ptr<int[]> pfw(new int[MXA]);
		int *fw = pfw.get();
		memset(fw, 0, sizeof(int)*MXA);
		int64_t ans = 0;
		for (int i=0; i<n; i++) {
			int a;
			scanf("%d", &a);
			int nle = fw_sum(fw, a);
			//fprintf(stderr, "sum=%d\n", nle);
			ans += i-nle;
			fw_inc(fw, MXA, a, 1);
		}
		printf("%" PRId64 "\n", ans);
	}
	return 0;
}
