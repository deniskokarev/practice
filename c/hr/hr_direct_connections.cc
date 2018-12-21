#include <cstdio>
#include <climits>
#include <algorithm>
/* Hackerrank https://www.hackerrank.com/challenges/direct-connections */
using namespace std;

constexpr int MOD = 1e9+7;
constexpr int MXP = 1e4+1;

void fw_inc(int *fw, int fw_sz, int x, int d) {
	for (int i=x; i<fw_sz; i|=i+1)
		fw[i] = (fw[i] + d) % MOD;
}

int fw_sum(const int *fw, int x) {
	int s = 0;
	for (int i=x; i>=0; i=(i&(i+1))-1)
		s = (s + fw[i]) % MOD;
	return s;
}

struct C {
	int x;
	int p;
};

int one_pass(const C *cc, int n, int aug) {
	int ans = 0;
	int fw_cnt[MXP];
	int fw_dist[MXP];
	fill(fw_cnt, fw_cnt+MXP, 0);
	fill(fw_dist, fw_dist+MXP, 0);
	for (int i=n-1; i>=0; i--) {
		int64_t sc = fw_sum(fw_cnt, cc[i].p+aug);
		int64_t sd = fw_sum(fw_dist, cc[i].p+aug);
		sd = sd + MOD - (sc * cc[i].x) % MOD;
		ans = (ans + cc[i].p * sd) % MOD;
		fw_inc(fw_cnt, MXP, cc[i].p, 1);
		fw_inc(fw_dist, MXP, cc[i].p, cc[i].x);
	}
	return ans;
}

int main(int argc, char **argv) {
	int t;
	scanf("%d", &t);
	while (t--) {
		int n;
		scanf("%d", &n);
		C cc[n];
		for (auto &c:cc)
			scanf("%d", &c.x);
		for (auto &c:cc)
			scanf("%d", &c.p);
		sort(cc, cc+n, [](const C &a, const C &b){return a.x < b.x;});
		int ans = one_pass(cc, n, 0);
		reverse(cc, cc+n);
		for (auto &c:cc)
			c.x = INT_MAX - c.x;
		ans += one_pass(cc, n, -1);
		printf("%d\n", ans % MOD);
	}
	return 0;
}
