class Solution {
public:
	static int minimumTeachings(int n, const vector<vector<int>>& lang, const vector<vector<int>>& ee) {
		int sz = lang.size();
		vector<vector<bool>> ll(sz, vector<bool>(n+1));
		for (int i=0; i<sz; i++)
			for (auto l:lang[i])
				ll[i][l] = true;
		vector<vector<int>> ee_fix;
		for (auto &e:ee) {
			int f = e[0] - 1;
			int t = e[1] - 1;
			bool fnd = false;
			for (int l=1; !fnd && l<=n; l++)
				fnd = ll[f][l] && ll[t][l];
			if (!fnd)
				ee_fix.push_back({f,t});
		}
		vector<bool> ll_fix(sz);
		for (auto &e:ee_fix)
			ll_fix[e[0]] = ll_fix[e[1]] = true;
		int mn = INT_MAX;
		for (int l=1; l<=n; l++) {
			int cnt = 0;
			for (int i=0; i<sz; i++)
				cnt += ll_fix[i] && !ll[i][l];
			mn = min(mn, cnt);
		}
		return mn;
	}
};
