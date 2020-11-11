class Solution {
public:
	static int bestTeamScore(const vector<int>& scores, const vector<int>& ages) {
		int sz = scores.size();
		vector<pair<int,int>> sa(sz);
		for (int i=0; i<sz; i++)
			sa[i] = {scores[i], ages[i]};
		sort(sa.begin(), sa.end());
		map<int,int> as; // age->score
		as[0] = 0;
		for (int i=0; i<sz; i++) {
			int score = sa[i].first;
			int age = sa[i].second;
			auto fnd = as.lower_bound(age);
			if (fnd != as.end() && fnd->first == age)
				fnd->second += score;
			else
				as[age] = prev(fnd)->second + score;
			fnd = as.find(age);
			int hi = fnd->second;
			++fnd;
			while (fnd != as.end() && fnd->second <= hi) {
				auto del = fnd;
				++fnd;
				as.erase(del);
			}
		}
		return prev(as.end())->second;
	}
};

