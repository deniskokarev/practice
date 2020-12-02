class Solution {
public:
	static int longestSubstring(const string &s, int k) {
		int sz = s.size();
		int mx = 0;
		for (int dr=1; dr<=26; dr++) { // desired number of different letters
			int h = 0; // sliding window head
			int ac = 0; // actual number of different letters
			int cnt[256]{0};
			int len = 0;
			int ok = 0; // number of letters with cnt >= k
			for (int t=0; t<sz; t++) {
				ac -= (cnt[s[t]] > 0);
				ok -= (cnt[s[t]] >= k);
				cnt[s[t]]++;
				ac += (cnt[s[t]] > 0);
				ok += (cnt[s[t]] >= k);
				len++;
				while (ac > dr) {
					ac -= (cnt[s[h]] > 0);
					ok -= (cnt[s[h]] >= k);
					cnt[s[h]]--;
					ac += (cnt[s[h]] > 0);
					ok += (cnt[s[h]] >= k);
					h++;
					len--;
				}
				mx = max(mx, len * (ok >= dr));
			}
		}
		return mx;
	}
};

