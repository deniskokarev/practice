class Solution {
	struct R {
		bool fnd;
		int mx;
	};
	static R maxUniqueSplit(const string &s, int f, int t, unordered_set<string> &seen) {
		R res;
		if (!seen.count(s.substr(f, t-f)))
			res = {true, 1};
		else
			res = {false, 0};
		for (int i=f+1; i<t; i++) {
			const string sstr = s.substr(f, i-f);
			if (!seen.count(sstr)) {
				seen.insert(sstr);
				R cres = maxUniqueSplit(s, i, t, seen);
				if (cres.fnd) {
					res.fnd = true;
					res.mx = max(res.mx, 1+cres.mx);
				}
				seen.erase(sstr);
			}
		}
		return res;
	}
public:
    static int maxUniqueSplit(const string &s) {
		unordered_set<string> seen;
		return maxUniqueSplit(s, 0, s.size(), seen).mx;
    }
};

