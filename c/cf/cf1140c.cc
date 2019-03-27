#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <cinttypes>
#define __STDC_FORMAT_MACROS // for PRId64 in mingw

/* CodeForces CF1140C problem */
using namespace std;

struct S {
	int t;
	int b;
};

int main(int argc, char **argv) {
	int n, k;
	scanf("%d%d", &n, &k);
	vector<S> ss(n);
	for (auto &s:ss)
		scanf("%d%d", &s.t, &s.b);
	sort(ss.begin(), ss.end(), [](const S &a, const S &b) {return a.b>b.b;});
	priority_queue<int, std::vector<int>, std::greater<int>> qq; // minheap
	int64_t mxlen = 0;
	int64_t ans = -1;
	for (auto &s:ss) {
		mxlen += s.t;
		qq.push(s.t);
		while (qq.size() > k) {
			mxlen -= qq.top();
			qq.pop();
		}
		ans = max(ans, mxlen*s.b);
	}
	printf("%" PRId64 "\n", ans);
	return 0;
}
