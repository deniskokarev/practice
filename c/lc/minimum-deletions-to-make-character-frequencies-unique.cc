class Solution {
public:
	static int minDeletions(const string &s) {
		int freq[26]{0};
		for (char c:s)
			freq[c-'a']++;
		sort(freq, freq+26, std::greater<int>());
		int sm = 0;
		int h = freq[0];
		int i;
		for (i=1; i<26 && h>0; i++) {
			if (freq[i] >= h) {
				sm += (freq[i]-h+1);
				h--;
			} else {
				h = freq[i];
			}
		}
		while (i<26 && freq[i]>0)
			sm += freq[i++];
		return sm;
	}
};

