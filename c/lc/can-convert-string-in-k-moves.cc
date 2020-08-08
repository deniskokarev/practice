class Solution {
public:
	static bool canConvertString(const string &s, const string &t, int k) {
		int sz = s.size();
		if (sz != t.size())
			return false;
		int diff_cnt[26]{0};
		for (int i=0; i<sz; i++)
			diff_cnt[(t[i]+26 - s[i]) % 26]++;
		diff_cnt[0] = 0;
		int tot_cnt = 0;
		for (int i=0; i<26; i++) {
			tot_cnt += diff_cnt[i];
		}
		int i;
		for (i=1; tot_cnt && i<=sz*26+1; i++) {
			if (diff_cnt[i%26]>0) {
				diff_cnt[i%26]--;
				tot_cnt--;
			}
		}
		return i-1 <= k;
	}
};
