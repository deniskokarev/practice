class Solution {
public:
	static int nextGreaterElement(int n) {
		string dd = to_string(n);
		int sz = dd.size();
		// solution(dd) = prefix(dd) + solution(suffix(dd)) for len(suffix) in range(2,len)
		if (sz < 2) {
			return -1;
		} else {
			multiset<char> sfx;
			sfx.insert(dd[sz-1]);
			for (int pos=sz-2; pos>=0; pos--) {
				sfx.insert(dd[pos]);
				auto fnd = sfx.upper_bound(dd[pos]);
				if (fnd != sfx.end()) {
					string res = dd.substr(0, pos);
					res += *fnd;
					sfx.erase(fnd);
					res += string(sfx.begin(), sfx.end());
					int64_t ans = stoll(res);
					if (ans < INT_MAX)
						return ans;
					else
						return -1;
				}
			}
			return -1;
		}
	}
};

