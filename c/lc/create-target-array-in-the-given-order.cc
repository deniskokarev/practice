class Solution {
public:
    vector<int> createTargetArray(vector<int>& nums, vector<int>& index) {
        list<int> t;
        for (int i=0; i<nums.size(); i++) {
            int p = index[i];
            auto ins_pos = t.begin();
            for (int j=0; j<p; j++)
                ++ins_pos;
            t.insert(ins_pos, nums[i]);
        }
        return vector<int>(t.begin(), t.end());
    }
};
