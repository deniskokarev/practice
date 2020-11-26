class Solution {
	struct IV {
		int f, t;
		IV(const vector<int> &v):f(v[0]),t(v[1]) {
		}
		bool operator<(const IV &o) const {
			return f<o.f || (f==o.f && t>o.t);
		}
	};
public:
	static int removeCoveredIntervals(const vector<vector<int>>& aivls) {
		int sz = aivls.size();
		vector<IV> ivls;
		for (auto &iv:aivls)
			ivls.push_back(iv);
		sort(ivls.begin(), ivls.end());
		int f = ivls[0].f;
		int t = ivls[0].t;
		int rm = 0;
		for (int i=1; i<sz; i++) {
			const IV &iv = ivls[i];
			if (ivls[i].t <= t) {
				rm++;
			} else {
				f = iv.f;
				t = iv.t;
			}
		}
		return sz-rm;
	}
};
