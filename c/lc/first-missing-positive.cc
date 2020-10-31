/* https://leetcode.com/problems/first-missing-positive/submissions/ */
class Solution {
public:
	static int firstMissingPositive(vector<int>& nums) {
		int sz = nums.size();
		// keep only [1..sz) elements
		int d=0;
		for (int s=0; s<sz; s++)
			if (0 < nums[s] && nums[s] <= sz)
				nums[d++] = nums[s]-1;
		sz = d;
		while (d < nums.size())
			nums[d++] = INT_MAX;
		// sort in-place
		for (int i=0; i<sz; i++) {
			// observe out of bounds and loops
			while (nums[i] != i && nums[i] != INT_MAX && nums[nums[i]] != nums[i]) {
				int s = nums[nums[i]];
				nums[nums[i]] = nums[i];
				nums[i] = s;
			}
			if (nums[i] != i)
				nums[i] = INT_MAX;
		}
		// find first missing
		for (int i=0; i<sz; i++)
			if (nums[i] == INT_MAX)
				return i+1;
		return sz+1;
	}
};

