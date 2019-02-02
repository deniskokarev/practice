#include <cstdio>
#include <queue>
/* Hackerrank https://www.hackerrank.com/challenges/deque-stl */

int main(int argc, char **argv) {
	int t;
	scanf("%d", &t);
	while (t--) {
		int n, k;
		scanf("%d%d", &n, &k);
		std::priority_queue<std::pair<int,int>> qq;
		for (int i=0; i<k; i++) {
			int v;
			scanf("%d", &v);
			qq.push(std::make_pair(v, i));
		}
		printf("%d ", qq.top().first);
		for (int i=k; i<n; i++) {
			int v;
			scanf("%d", &v);
			qq.push(std::make_pair(v, i));
			while (qq.top().second <= i-k)
				qq.pop();
			printf("%d ", qq.top().first);
		}
		printf("\n");
	}
	return 0;
}
