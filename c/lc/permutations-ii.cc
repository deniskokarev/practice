// https://leetcode.com/problems/permutations-ii/

constexpr int EMPTY = -11;

class Solution {
    void perm(vector<vector<int>> &res, vector<int> &cur, const vector<int> &nums, int pos) {
        int sz = cur.size();
        if (pos == sz) {
            res.push_back(cur);
            return;
        }
        for (int i=0; i<sz; i++) {
            if (cur[i] == nums[pos]) {
                return;
            }
            if (cur[i] == EMPTY) {
                cur[i] = nums[pos];
                perm(res, cur, nums, pos+1);
                cur[i] = EMPTY;
            }
        }
    }
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> cur(nums.size(), EMPTY);
        perm(res, cur, nums, 0);
        return res;
    }
};
