// https://leetcode.com/problems/divide-array-into-arrays-with-max-difference
class Solution {
public:
    vector<vector<int>> divideArray(vector<int> &nums, int k) {
        int sz = nums.size();
        int s3 = sz / 3;
        vector<vector<int>> ans(s3, vector<int>(3));
        sort(begin(nums), end(nums));
        for (int i3 = 0; i3 < s3; i3++) {
            int i = 3 * i3;
            int mn = nums[i];
            int mx = nums[i + 2];
            if (mx - mn <= k) {
                for (int j = 0; j < 3; j++) {
                    ans[i3][j] = nums[i + j];
                }
            } else {
                return {};
            }
        }
        return ans;
    }
};

