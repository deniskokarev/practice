class Solution {
public:
    int maxOperations(vector<int>& nums, int k) {
        unordered_map<int,int> hh;
        int cnt=0;
        for (int n:nums) {
            auto fnd = hh.find(k-n);
            if (fnd != hh.end() && fnd->second > 0) {
                cnt++;
                fnd->second--;
            } else {
                hh[n]++;
            }
        }
        return cnt;
    }
};
