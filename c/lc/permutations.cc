class Solution {
    vector<vector<int>> permute_r(const vector<int>& nums, int pos) {
        if (pos < nums.size()-1) {
            vector<vector<int>> res;
            for (vector<int> &p_c:permute_r(nums, pos+1)) {
                for (int j=0; j<=p_c.size(); j++) {
                    res.push_back(p_c);
                    auto &v = res.back();
                    v.insert(v.begin()+j, nums[pos]);
                }
            }
            return res;
        } else {
            return {{nums[pos]}};
        }
    }
public:
    vector<vector<int>> permute(const vector<int>& nums) {
        return permute_r(nums, 0);
    }
};
