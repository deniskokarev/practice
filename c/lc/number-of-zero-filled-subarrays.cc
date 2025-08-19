// https://leetcode.com/problems/number-of-zero-filled-subarrays
class Solution {
public:
	long long zeroFilledSubarray(const vector<int>& nums) {
		int64_t sm = 0;
		int z_cnt = 0;
		for (int n:nums) {
			z_cnt++;
			if (n != 0) {
				z_cnt = 0;
			}
			sm += z_cnt;
		}
		return sm;
	}
};


class Solution {
public:
    static long long zeroFilledSubarray(const vector<int>& nums) {
        long long sm = 0;
        int z = 0;
        int sz = nums.size();
        for (auto n:nums) {
            z = (z+1) * (!n);
            sm += z;
        }
        return sm;
    }
};
