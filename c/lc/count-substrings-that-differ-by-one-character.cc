class Solution {
public:
	static int countSubstrings(const string &s, const string &t) {
		vector<vector<int>> ll(s.size()+2, vector<int>(t.size()+2));
		vector<vector<int>> rr(s.size()+2, vector<int>(t.size()+2));
		for (int si=0; si<s.size(); si++)
			for (int ti=0; ti<t.size(); ti++)
				ll[si+1][ti+1] = (ll[si][ti]+1) * (s[si] == t[ti]);
		for (int si=s.size()-1; si>=0; si--)
			for (int ti=t.size()-1; ti>=0; ti--)
				rr[si+1][ti+1] = (rr[si+2][ti+2]+1) * (s[si] == t[ti]);
		int ans = 0;
		for (int si=1; si<=s.size(); si++)
			for (int ti=1; ti<=t.size(); ti++)
				ans += (ll[si][ti] == 0) * (ll[si-1][ti-1]+1) * (rr[si+1][ti+1]+1);
		return ans;
	}
};

