// https://leetcode.com/contest/weekly-contest-212/problems/arithmetic-subarrays/
class Solution {
public:
	static vector<bool> checkArithmeticSubarrays(const vector<int>& nums, const vector<int>& ll, const vector<int>& rr) {
		int m = ll.size();
		vector<bool> ans(m);
		for (int i=0; i<m; i++) {
			int l = ll[i];
			int r = rr[i];
			int len = r-l+1;
			if (len < 3) {
				ans[i] = true;
			} else {
				vector<int> sub(len);
				copy(nums.begin()+l, nums.begin()+r+1, sub.begin());
				sort(sub.begin(), sub.end());
				bool r = true;
				for (int j=2; j<len; j++)
					r &= (sub[j]-sub[j-1]) == (sub[j-1]-sub[j-2]);
				ans[i] = r;
			}
		}
		return ans;
	}
};

