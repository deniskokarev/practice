class Solution {
    void perm(vector<int> &sel, int dep, bitset<8> taken, const vector<int>& nums, vector<vector<int>> &out) {
        if (dep < 0) {
            out.push_back(sel);
        } else {
            int lst = -11;
            for (int i=0; i<nums.size(); i++) {
                if (!taken[i] && nums[i] != lst) {
                    sel[dep] = nums[i];
                    lst = nums[i];
                    taken[i] = 1;
                    perm(sel, dep-1, taken, nums, out);
                    taken[i] = 0;
                }
            }
        }
    }
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        int sz = nums.size();
        vector<int> sel(sz);
        vector<vector<int>> out;
        sort(nums.begin(), nums.end());
        perm(sel, sz-1, 0, nums, out);
        return out;
    }
};
