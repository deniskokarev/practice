#include <cstdio>
#include <climits>
#include <cinttypes>
#include <vector>
#include <algorithm>
/* Hackerrank https://www.hackerrank.com/challenges/balanced-forest/problem */
using namespace std;

struct T {
	int64_t sum;
	int parent;
	int id;
	bool operator<(const T &o) const {
		return sum < o.sum;
	}
};

int64_t bld_tree(vector<T> &tree, const vector<vector<int>> &gg, const vector<int64_t> &vv, int root, int parent) {
	tree[root] = T {vv[root], parent, root};
	for (auto v:gg[root])
		if (v != parent)
			tree[root].sum += bld_tree(tree, gg, vv, v, root);
	return tree[root].sum;
}	

bool is_parent(const vector<T> &tree, int parent, int chld) {
	while (chld > 0) {
		chld = tree[chld].parent;
		if (chld == parent)
			return true;
	}
	return false;
}

int64_t solve(const vector<T> &tree, int n) {
	vector<T> srtree(tree);
	sort(srtree.begin(), srtree.end());
	int64_t res = LLONG_MAX;
	for (int i=n-1; i>0; i--) {
		bool odd = (tree[0].sum + tree[i].sum) & 1;
		if (tree[i].sum*3 > tree[0].sum || odd)
			continue;
		T key {(tree[0].sum - tree[i].sum)/2, -1, -1};
		for (auto fnd = lower_bound(srtree.begin(), srtree.end(), key); fnd != srtree.end() && fnd->sum == key.sum; ++fnd)
			if (fnd->id != i && fnd->id != 0 && !is_parent(tree, fnd->id, i))
				res = min(res, key.sum - tree[i].sum);
		key = T {(tree[0].sum + tree[i].sum)/2, -1, -1};
		for (auto fnd = lower_bound(srtree.begin(), srtree.end(), key); fnd != srtree.end() && fnd->sum == key.sum; ++fnd)
			if (fnd->id != i && fnd->id != 0 && !is_parent(tree, fnd->id, i))
				res = min(res, key.sum - 2*tree[i].sum);
	}
	for (int i=n-1; i>0; i--) {
		if (tree[i].sum*3 < tree[0].sum)
			continue;
		T key {tree[i].sum, -1, -1};
		for (auto fnd = lower_bound(srtree.begin(), srtree.end(), key); fnd != srtree.end() && fnd->sum == key.sum; ++fnd)
			if (fnd->id != i && fnd->id != 0)
				res = min(res, tree[i].sum*3 - tree[0].sum);
	}
	if (res < LLONG_MAX)
		return res;
	else
		return -1;
}

int main(int argc, char **argv) {
	int q;
	scanf("%d", &q);
	while (q--) {
		int n;
		scanf("%d", &n);
		vector<int64_t> vv(n);
		for (auto &v:vv)
			scanf("%" PRId64, &v);
		vector<vector<int>> gg(n);
		for (int i=0; i<n-1; i++) {
			int f, t;
			scanf("%d%d", &f, &t);
			f--, t--;
			gg[f].push_back(t);
			gg[t].push_back(f);
		}
		vector<T> tree(n);
		bld_tree(tree, gg, vv, 0, -1);
		printf("%" PRId64 "\n", solve(tree, n));
	}
}
