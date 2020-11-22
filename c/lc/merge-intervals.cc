class Solution {
public:
	vector<vector<int>> merge(vector<vector<int>>& inter) {
		int sz = inter.size();
		sort(inter.begin(), inter.end());
		int l = inter[0][0];
		int r = inter[0][1];
		vector<vector<int>> res;
		for (int i=1; i<sz; i++) {
			if (inter[i][0] > r) {
				res.push_back({l,r});
				l = inter[i][0];
				r = inter[i][1];
			} else {
				r = max(r, inter[i][1]);
			}
		}
		res.push_back({l,r});
		return res;
	}
};

