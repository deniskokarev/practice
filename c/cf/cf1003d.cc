#include <cstdio>
#include <algorithm>
/* CodeForces CF1003D problem */
using namespace std;

int solve(const int cnt[32], int b) {
	int ans = 0;
	for (int i=30,p2=1<<30; i>=0 && b > 0; i--,p2>>=1) {
		int q = b/p2;
		int c = min(q, cnt[i]);
		ans += c;
		b -= c*p2;
	}
	if (b == 0)
		return ans;
	else
		return -1;
}

int main(int argc, char **argv) {
	int cnt[32] {0};
	int n, q;
	scanf("%d%d", &n, &q);
	while (n--) {
		int a;
		scanf("%d", &a);
		for (int i=0; i<31; i++,a>>=1)
			if ((a&1))
				cnt[i]++;
	}
	while (q--) {
		int b;
		scanf("%d", &b);
		printf("%d\n", solve(cnt, b));
	}
	return 0;
}
