/* ACMP 1081 */
#include <cstdio>

using namespace std;

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	unsigned long long aa[n+1];
	aa[0] = 0;
	for (int i=1; i<=n; i++) {
		int d;
		scanf("%d", &d);
		aa[i] = aa[i-1]+d;
	}
	int m;
	scanf("%d", &m);
	while (m-- > 0) {
		int l, r;
		scanf("%d%d", &l, &r);
		printf("%llu ", (aa[r] - aa[l-1]));
	}
	printf("\n");
	return 0;
}
