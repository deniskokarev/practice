class Solution {
public:
    int specialArray(vector<int>& nums) {
        constexpr int MX = 1000;
        vector<int> nn(MX+1);
        for (int n:nums)
            nn[n]++;
        int sm = 0;
        for (int j=MX; j>=0; j--) {
            sm += nn[j];
            if (sm == j)
                return j;
        }
        return -1;
    }
};
