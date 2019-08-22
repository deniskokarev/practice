#include <iostream>
/* https://leetcode.com/contest/weekly-contest-150/problems/last-substring-in-lexicographical-order/ */
using namespace std;

class Solution {
	static constexpr int base = 13;
	struct SSTR {
		int ofs, sz;
	};
	// hash-assisted comparison by looking at common prefix
	struct SSTR_CMP {
		const uint64_t *ss_hpow;
		const uint64_t *ss_hash;
		const string &s;
		const int sz;
		bool operator()(const SSTR &a, const SSTR &b) {
			int mnl = min(a.sz, b.sz);
			// upper-bound search
			int f=1, t=mnl+1;
			while (f<t) {
				int m = f+(t-f)/2;
				uint64_t ha = (ss_hash[a.ofs+m]-ss_hash[a.ofs])*ss_hpow[sz-a.ofs-m];
				uint64_t hb = (ss_hash[b.ofs+m]-ss_hash[b.ofs])*ss_hpow[sz-b.ofs-m];
				if (ha == hb)
					f = m+1;
				else
					t = m;
			}
			if (f<=mnl)
				return s[a.ofs+f-1] < s[b.ofs+f-1];
			else
				return (a.sz) < (b.sz);
		}
	};
public:
	static string lastSubstring(const string &s) {
		int sz = s.size();
		uint64_t ss_hpow[sz+1];
		ss_hpow[0] = 1;
		uint64_t ss_hash[sz+1];
		ss_hash[0] = 0;
		for (int i=0; i<sz; i++) {
			ss_hpow[i+1] = ss_hpow[i]*base;
			ss_hash[i+1] = ss_hash[i]+ss_hpow[i+1]*s[i];
		}
		SSTR mx {0, sz};
		auto cmp_less = SSTR_CMP {ss_hpow, ss_hash, s, sz};
		for (int i=1; i<sz; i++) {
			SSTR ss {i, sz-i};
			if (cmp_less(mx, ss))
				mx = ss;
		}
		return s.substr(mx.ofs, mx.sz);
	}
};

int main(int argc, char **argv) {
	cout << Solution::lastSubstring("abab") << '\n';
	cout << Solution::lastSubstring("leetcode") << '\n';
	return 0;
}
