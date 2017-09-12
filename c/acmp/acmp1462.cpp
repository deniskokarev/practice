/* ACMP 1462 */
#include <queue>
#include <vector>
#include <algorithm>
#include <stdio.h>

using namespace std;

int main(int argc, char **argv) {
	int n, k;
	scanf("%d%d", &n, &k);
	vector<pair<int,int>> pp(n);
	for (auto &p:pp)
		scanf("%d%d", &p.first, &p.second);
	sort(pp.begin(), pp.end(), greater<pair<int,int>>());
	priority_queue<int, vector<int>, greater<int>> qq;
	for (int i=0; i<k; i++)
		qq.push(pp[i].second);
	uint64_t mx = ((uint64_t)pp[k-1].first)*qq.top();
	for (int i=k; i<pp.size(); i++) {
		if (qq.top()<pp[i].second) {
			qq.pop();
			qq.push(pp[i].second);
			mx = max(mx, ((uint64_t)qq.top())*pp[i].first);
		}
	}
	printf("%lld\n", mx);
	return 0;
}
