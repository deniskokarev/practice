#include <cstdio>
#include <vector>
#include <algorithm>
/* CodeForces CF1077C problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	vector<pair<int64_t,int>> aa(n);
	int64_t sum = 0;
	for (int i=0; i<n; i++) {
		int a;
		scanf("%d", &a);
		aa[i] = make_pair(a,i);
		sum += a;
	}
	sort(aa.begin(), aa.end());
	int ans[n];
	int ans_sz = 0;
	for (auto a:aa) {
		int64_t r = sum-a.first;
		if (r % 2 == 0) {
			auto lb = lower_bound(aa.begin(), aa.end(), make_pair(r/2-1, n+1));
			auto ub = upper_bound(aa.begin(), aa.end(), make_pair(r/2, n+1));
			while (lb < ub) {
				if (lb->second != a.second) {
					ans[ans_sz++] = a.second;
					break;
				}
				lb++;
			}
		}
	}
	printf("%d\n", ans_sz);
	for (int i=0; i<ans_sz; i++)
		printf("%d ", ans[i]+1);
	printf("\n");
	return 0;
}
