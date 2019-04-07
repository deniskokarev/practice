#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
/* CodeForces CF1143C problem */
using namespace std;

struct N {
	int id;
	int p;
	int c;
	int nc; // num of child
	int nb; // num of bad child
};

void dfs(const vector<vector<int>> &gg, vector<N> &tree, int root) {
	for (int c:gg[root]) {
		dfs(gg, tree, c);
		tree[root].nc++;
		tree[root].nb += tree[c].c;
	}
}

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	vector<N> tree(n);
	int i = 0;
	int root = -1;
	vector<vector<int>> gg(n);
	priority_queue<int,vector<int>,std::greater<int>> qq;
	for (auto &t:tree) {
		t.id = i;
		scanf("%d%d", &t.p, &t.c);
		t.p--;
		if (t.p < 0)
			root = i;
		else
			gg[t.p].push_back(i);
		t.nc = t.nb = 0;
		qq.push(i);
		i++;
	}
	dfs(gg, tree, root);
	int cnt = 0;
	while (!qq.empty()) {
		int top = qq.top();
		qq.pop();
		auto &t = tree[top];
		if (!t.c || t.nc != t.nb)
			continue;
		printf("%d ", top+1);
		cnt++;
	}
	if (!cnt)
		printf("-1\n");
	else
		printf("\n");
	return 0;
}
