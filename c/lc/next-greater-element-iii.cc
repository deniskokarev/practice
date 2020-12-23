struct R {
	bool ok;
	string s;
};

class Solution {
	static R solution(const string &dd, int sfx_len) {
		if (sfx_len < 2) {
			return {false, ""};
		} else {
			int sz = dd.size();
			multiset<char> ad(dd.begin() + sz - sfx_len + 1, dd.end()); // "abcd", 2 -> {"d"}
			auto fnd = ad.upper_bound(dd[sz-sfx_len]);
			if (fnd != ad.end()) {
				char d = *fnd;
				ad.erase(fnd);
				ad.insert(dd[sz-sfx_len]);
				return {true, d + string(ad.begin(), ad.end())};
			} else {
				return {false, ""};
			}
		}
	}
public:
	static int nextGreaterElement(int n) {
		string dd = to_string(n);
		int sz = dd.size();
		// solution(dd) = prefix(dd) + solution(suffix(dd)) for len(suffix) in range(2,len)
		for (int sfx_len=2; sfx_len<=sz; sfx_len++) {
			R res = solution(dd, sfx_len);
			if (res.ok) {
				int64_t ans = stoll(dd.substr(0, sz-sfx_len) + res.s);
				if (ans > INT_MAX)
					return -1;
				else
					return ans;
			}
		}
		return -1;
	}
};

