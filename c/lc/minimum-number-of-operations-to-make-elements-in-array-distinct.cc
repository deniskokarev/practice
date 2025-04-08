// https://leetcode.com/problems/minimum-number-of-operations-to-make-elements-in-array-distinct
class Solution {
public:
	static int minimumOperations(const vector<int> &nums) {
		int sz = nums.size();
		vector<bool> dup(101);
		int i = sz - 1;
		while (i >= 0 && !dup[nums[i]]) {
			dup[nums[i--]] = true;
		}
		return (i + 3) / 3;
	}
};
