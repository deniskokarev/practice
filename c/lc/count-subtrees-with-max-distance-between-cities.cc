class Solution {
	static constexpr int MX = 15;
	struct R {
		int dep;
		int seen;
	};
	static R mx_dep_dfs(const vector<vector<int>> &gg, int root, int p, const bitset<MX> &may_visit) {
		R res {0,1<<root};
		for (int c:gg[root]) { 
			if (c != p && may_visit[c]) {
				R cr = mx_dep_dfs(gg, c, root, may_visit);
				res.dep = max(res.dep, cr.dep);
				res.seen |= cr.seen; 
			}
		}
		res.dep++;
		return res;
	}
public:
	static vector<int> countSubgraphsForEachDiameter(int n, const vector<vector<int>>& edges) {
		vector<vector<int>> gg(n);
		for (auto &e:edges) {
			gg[e[0]-1].push_back(e[1]-1);
			gg[e[1]-1].push_back(e[0]-1);
		}
		vector<int> diam(1<<n);
		for (int i=0; i < (1<<n); i++) {
			for (int root=0; root<n; root++) {
				R res = mx_dep_dfs(gg, root, -1, i);
				diam[res.seen] = max(diam[res.seen], res.dep-1);
			}
		}
		vector<int> ans(n-1);
		for (int i=0; i < (1<<n); i++)
			if (diam[i])
				ans[diam[i]-1]++;
		return ans;
	}
};
