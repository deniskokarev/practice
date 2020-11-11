class Solution {
	static constexpr int MXA = 1000;
public:
	static int bestTeamScore(const vector<int>& scores, const vector<int>& ages) {
		int sz = scores.size();
		vector<pair<int,int>> sa(sz);
		for (int i=0; i<sz; i++)
			sa[i] = {scores[i], ages[i]};
		sort(sa.begin(), sa.end());
		vector<int> as(MXA+1); // age->sum
		for (int i=0; i<sz; i++) {
			int score = sa[i].first;
			int age = sa[i].second;
			int mx = -1;
			for (int a=0; a<=age; a++)
				mx = max(mx, as[a]);
			as[age] = mx + score;
		}
		return *max_element(as.begin(), as.end());
	}
};

