class Solution {
public:
	static int numberOfSubstrings(const string &s) {
		int h=0,t=0;
		int sz = s.size();
		int cnt[3]{0};
		int ans = 0;
		for (h=0; h<sz; h++) {
			int ch_h = s[h]-'a';
			cnt[ch_h]++;
			if (cnt[0] && cnt[1] && cnt[2]) {
				while (cnt[0] && cnt[1] && cnt[2] && t<h) {
					int ch_t = s[t]-'a';
					cnt[ch_t]--;
					t++;
				}
			}
			ans += t;
		}
		return ans;
	}
};

