// https://leetcode.com/problems/find-all-k-distant-indices-in-an-array
class Solution {
public:
	static vector<int> findKDistantIndices(const vector<int> &nums, int key, int k) {
		vector<int> kpos;
		int sz = nums.size();
		kpos.push_back(-k - 1);
		for (auto i = 0; i < sz; i++) {
			if (nums[i] == key) {
				kpos.push_back(i);
			}
		}
		kpos.push_back(sz + k + 1);
		vector<int> res;
		int i = 0, kp = 0;
		while (i < sz) {
			if (kpos[kp] + k >= i || i >= kpos[kp + 1] - k) {
				res.push_back(i);
			}
			if (i == kpos[kp + 1]) {
				kp++;
			}
			i++;
		}
		return res;
	}
};
