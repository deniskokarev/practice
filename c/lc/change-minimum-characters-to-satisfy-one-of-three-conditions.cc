class Solution {
public:
	static int minCharacters(const string a, const string b) {
		int cnt_a[27]{};
		for (char c:a)
			cnt_a[c-'a'+1]++;
		int cnt_b[27]{};
		for (char c:b)
			cnt_b[c-'a'+1]++;
		int sm_a = 0, sm_b = 0;
		for (int i=1; i<27; i++) {
			sm_a += cnt_a[i];
			sm_b += cnt_b[i];
			cnt_a[i] += cnt_a[i-1];
			cnt_b[i] += cnt_b[i-1];
		}
		// find best if modify both to same middle
		int mn = INT_MAX;
		for (int m=1; m<27; m++) {
			int ca = cnt_a[m-1] + (sm_a-cnt_a[m]); 
			int cb = cnt_b[m-1] + (sm_b-cnt_b[m]);
			mn = min(mn, ca+cb);
		}
		// find best when one greater the other
		for (int m=2; m<27; m++) {
			// bring a below b
			mn = min(mn, sm_a - cnt_a[m-1] + cnt_b[m-1]);
			// bring b below a
			mn = min(mn, sm_b - cnt_b[m-1] + cnt_a[m-1]);
		}
		return mn;
	}
};
