// https://leetcode.com/problems/longest-duplicate-substring
class Solution {
	static constexpr int HBASE = 13;
	static bool has_dups(const string_view &s, string_view &res, int w) {
		int sz = s.size();
		unordered_map<size_t, vector<int>> hh(sz*10);
		size_t hash = 0;
		size_t hbase_pow = 1;
		for (int i=0; i<w; i++) {
			hash = hash*HBASE+s[i];
			hbase_pow *= HBASE;
		}
		hh[hash].push_back(w-1);
		for (int i=w; i<sz; i++) {
			hash = hash*HBASE+s[i];
			hash -= s[i-w]*hbase_pow;
			// had to do exact check
			for (int r:hh[hash]) {
				if (s.substr(r-w+1, w) == s.substr(i-w+1, w)) {
					res = s.substr(i-w+1, w);
					return true;
				}
			}
			hh[hash].push_back(i);
		}
		return false;
	}
public:
	static string longestDupSubstring(const string &s) {
		int sz = s.size();
		int mn=1, mx=sz-1;
		string_view res;
		while (mn <= mx) {
			int m = (mn+mx)/2;
			if (!has_dups(s, res, m))
				mx = m-1;
			else
				mn = m+1;
		}
		if (res.size())
			return string(res);
		else
			return "";
	}
};

