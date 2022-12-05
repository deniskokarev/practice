// https://leetcode.com/problems/minimum-average-difference/
#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

class Solution {
public:
	static int minimumAverageDifference(const vector<int> &nums) {
		int sz = nums.size();
		int64_t sm = accumulate(begin(nums), end(nums), 0L);
		int64_t lsm = 0;
		int mn_idx = sz - 1;
		int mn_diff = INT_MAX;
		for (int i = 0; i < sz - 1; i++) {
			lsm += nums[i];
			int64_t rsm = sm - lsm;
			int la = lsm / (i + 1);
			int ra = rsm / (sz - i - 1);
			int diff = abs(la - ra);
			if (diff < mn_diff) {
				mn_diff = diff;
				mn_idx = i;
			}
		}
		// last el
		int la = sm / sz;
		int ra = 0;
		if (abs(la - ra) < mn_diff)
			mn_idx = sz - 1;
		return mn_idx;
	}
};

int main(int argc, char **argv) {
	cout << Solution::minimumAverageDifference({2, 5, 3, 9, 5, 3}) << endl;
	cout << Solution::minimumAverageDifference({0}) << endl;
	cout << Solution::minimumAverageDifference({4, 2, 0}) << endl;
	return 0;
}
