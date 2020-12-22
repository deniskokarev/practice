class Solution {
public:
	static int smallestRangeII(const vector<int>& aa, int k) {
		if (aa.size() > 1) {
			set<pair<int,bool>> ss;
			for (int a:aa)
				ss.insert({a,false});
			// from everything combed to left we're tring to comb
			// left border to right
			// >>  <<<<<<
			int mn_diff = prev(ss.end())->first - ss.begin()->first;
			auto it = ss.begin();
			while (it != ss.end()) {
				if (!it->second) {
					ss.insert({it->first+2*k, true});
					auto nit = next(it);
					ss.erase(it);
					it = nit;
				} else {
					++it;
				}
				mn_diff = min(mn_diff, prev(ss.end())->first - ss.begin()->first);
			}
			return mn_diff;
		} else {
			return 0;
		}
	}
};

