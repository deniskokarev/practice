#define __STDC_FORMAT_MACROS // for PRId64 in mingw
#include <cinttypes>
#include <cstdio>
#include <unordered_map>
/* https://www.hackerrank.com/challenges/pairs */

using namespace std;

int main(int argc, char **argv) {
	int n, k;
	scanf("%d%d", &n, &k);
	unordered_map<int,int> bf(1e6+3);
	int64_t ans = 0;
	while (n--) {
		int a;
		scanf("%d", &a);
		ans += bf[a-k];
		ans += bf[a+k];
		bf[a]++;
	}
	printf("%" PRId64 "\n", ans);
	return 0;
}
