// https://leetcode.com/problems/palindrome-partitioning-ii/
// CPU: O(n^2)
// MEM: O(n)
class Solution {
public:
	int minCut(const string &s) {
		// plX[f] - max palindrome length starting at f
		// means s[f..plX[f]] is palindrome, only we need to consider even and odd
		//	   separately
		// ans[t+1] - best solution on prefix s[0..t]
		int sz = s.size();
		int ple[sz], plo[sz];
		int (*pl[2]) {ple, plo};
		fill(ple, ple+sz, 0);
		fill(plo, plo+sz, 1);
		int ans[sz+1];
		ans[0] = 0;
		ans[1] = 1;
		for (int t=1; t<sz; t++) {
			ans[t+1] = ans[t]+1;
			for (int f=0; f<t; f++) {
				if (s[f] == s[t]) {
					int odd = (t-f+1)&1;
					if (f + pl[odd][f+1] == t-1) {
						pl[odd][f] = pl[odd][f+1] + 2;
						ans[t+1] = min(ans[t+1], ans[f] + 1);
					}
				}
			}
		}
		return ans[sz]-1;
	}
};
