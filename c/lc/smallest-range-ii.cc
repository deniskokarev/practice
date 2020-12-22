class Solution {
public:
	static int smallestRangeII(const vector<int>& aa, int k) {
		if (aa.size() > 1) {
			vector<int> ss(aa);
			sort(ss.begin(), ss.end());
			int sz = unique(ss.begin(), ss.end()) - ss.begin();
			ss.resize(sz);
			// from everything combed to left we're trying to comb
			// left border to right
			// >>  <<<<<<
			int mx = ss[sz-1];
			int mn = ss[0];
			int mn_diff = mx - mn;
			int mn_mn = ss[0] + 2*k; // absolute minimum we can reach
			for (int i=0; i < sz-1 && mn < mn_mn; i++) {
				if (ss[i] + 2*k > mx) {
					mx = ss[i] + 2*k;
					mn = ss[i+1];
				} else {
					mn = min(ss[i]+2*k, ss[i+1]);
				}
				mn = min(mn_mn, mn);
				mn_diff = min(mn_diff, mx - mn);
			}
			return mn_diff;
		} else {
			return 0;
		}
	}
};

