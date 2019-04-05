#include <cstdio>
#include <vector>
#include <algorithm>
/* ICPC https://judge.icpc.global/problems/hobsonstrains */
using namespace std;

struct VL {
	int nloop;
	int idx;
};

static int dfs(const vector<vector<int>> &ef,
			   const vector<int> &loop,
			   int root_loop_idx,
			   int root,
			   vector<int> &up,
			   int depth,
			   int k,
			   vector<int> &cnt)
{
	if (depth >= k) {
		cnt[up[depth-k]]--;
	} else {
		int lsz = loop.size();
		int d = min(k-depth, lsz-1);
		cnt[loop[(root_loop_idx+d) % lsz]]--;
	}
	up[depth] = root;
	for (auto f:ef[root])
		if (f > 0)
			cnt[root] += dfs(ef, loop, root_loop_idx, f, up, depth+1, k, cnt);
	return cnt[root];
}

int main(int argc, char **argv) {
	int n, k;
	scanf("%d%d", &n, &k);
	k++;
	vector<int> et(n+1);
	vector<vector<int>> ef(n+1); // ef[s].size() == 0 means s is a start
	vector<VL> vl(n+1, VL{-1,-1}); // which loop the vertice belongs to and what's its index in the ring
	vector<vector<int>> loop;
	for (int i=1; i<=n; i++) {
		int t;
		scanf("%d", &t);
		et[i] = t;
		ef[t].push_back(i);
	}
	// decompose the graph into loops
	vector<int> seen(n+1);
	int tick = 0;
	for (int i=1; i<=n; i++) {
		if (!seen[i]) {
			int btick = tick;
			vector<int> this_loop;
			int j = i;
			while (!seen[j]) {
				this_loop.push_back(j);
				seen[j] = tick++;
				j = et[j];
			}
			if (seen[j] >= btick) {
				int len = tick-seen[j];
				loop.push_back(vector<int>(len));
				auto &l = loop.back();
				copy(this_loop.begin()+this_loop.size()-len, this_loop.end(), l.begin());
				for (int k=0; k<len; k++)
					vl[l[k]] = VL { int(loop.size()-1), k };
			}
		}
	}
#if 1
	for (auto &l:loop) {
		for (auto i:l)
			fprintf(stderr, "%d ", i);
		fprintf(stderr, "\n");
	}
#endif
	// now handle trees growing from loops
	vector<int> cnt(n+1, 1);
	vector<int> up(n+1);
	for (int i=1; i<=n; i++) {
		if (vl[i].nloop != -1 && ef[i].size() > 1) {
			for (auto &f:ef[i])
				if (vl[f].nloop != -1)
					f = -1; // isolate the tree from loop
			cnt[i] = dfs(ef, loop[vl[i].nloop], vl[i].idx, i, up, 0, k, cnt);
		}
	}
#if 0
	// finish computing
	for (auto &l:loop) {
		int lsz = l.size();
		for (int i=0; i<lsz; i++) {
			int j = (i+1)%lsz;
			cnt[l[j]] += cnt[l[i]];
		}
	}
#endif
	for (int i=1; i<=n; i++)
		printf("%d\n", cnt[i]);
	return 0;
}
