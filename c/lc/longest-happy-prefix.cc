template <typename RIC, typename RIN> inline void prefix_function(const RIC s, size_t sz, RIN pp) {
	size_t k = 0;
	pp[0] = 0;
	for (size_t i=1; i<sz; i++) {
		for (; k>0 && s[i] != s[k]; k=pp[k-1]);
		if (s[i] == s[k]) {
			k++;
			pp[i] = k;
		} else {
			pp[i] = 0;
		}
	}
}

class Solution {
public:
	static string longestPrefix(const string &s) {
		int sz = s.size();
		int pfx[sz];
		prefix_function(s, sz, pfx);
		return s.substr(0, pfx[sz-1]);
	}
};
