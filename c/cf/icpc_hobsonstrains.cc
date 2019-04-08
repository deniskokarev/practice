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
	int lsz = loop.size();
	if (depth >= k) {
		cnt[up[depth-k]]--;
	} else {
		int d = min(k-depth, lsz);
		int ms = (root_loop_idx+d) % lsz;
		cnt[loop[ms]]--;
		if (ms <= root_loop_idx)
			cnt[loop[0]]++; // if end wraps around ringbuf
	}
	up[depth] = root;
	cnt[root]++;
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
#if 0
	// detected loops
	for (auto &l:loop) {
		for (auto i:l)
			fprintf(stderr, "%d ", i);
		fprintf(stderr, "\n");
	}
#endif
	// now handle trees growing from loops
	vector<int> cnt(n+1, 0);
	vector<int> up(n+1);
	for (int li=0; li<loop.size(); li++) {
		auto &l = loop[li];
		for (int ni=0; ni<l.size(); ni++) {
			int node = l[ni];
			for (auto &f:ef[node])
				if (vl[f].nloop != -1)
					f = -1; // isolate the node from loop
			(void)dfs(ef, l, ni, node, up, 0, k, cnt);
		}
	}
	// final loop nodes computation
	for (auto &l:loop) {
		int lsz = l.size();
		for (int i=0; i<lsz-1; i++)
			cnt[l[i+1]] += cnt[l[i]];
	}
	for (int i=1; i<=n; i++)
		printf("%d\n", cnt[i]);
	return 0;
}
