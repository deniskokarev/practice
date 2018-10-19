#define __STDC_FORMAT_MACROS // for PRId64 in mingw
#include <cstdio>
#include <cinttypes>
#include <queue>
/* INF 113076 */

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	std::priority_queue<int64_t, std::vector<int64_t>, std::greater<int64_t>> qq;
	while (n--) {
		int p;
		scanf("%d", &p);
		qq.push(p);
	}
	int64_t ans = 0;
	while (qq.size()>1) {
		auto p1 = qq.top();
		qq.pop();
		auto p2 = qq.top();
		qq.pop();
		ans += p1+p2;
		qq.push(p1+p2);
	}
	printf("%" PRId64 "\n", ans);
	return 0;
}
