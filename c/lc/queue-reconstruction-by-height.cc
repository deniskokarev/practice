// https://leetcode.com/problems/queue-reconstruction-by-height
class Solution {
public:
	static vector<vector<int>> reconstructQueue(vector<vector<int>>& pp) {
		sort(pp.begin(), pp.end(), [](const vector<int> &a, const vector<int> &b){return a[0]>b[0] || (a[0]==b[0] && a[1] < b[1]);});
		list<vector<int>> res;
		for (const auto &p:pp) {
			int h = p[0];
			int k = p[1];
			auto it = res.begin();
			while (k) {
				if ((*it)[0] >= h)
					k--;
				++it;
			}
			res.insert(it, p);
		}
		return vector<vector<int>>(res.begin(), res.end());
	}
};

