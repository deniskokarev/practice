// https://leetcode.com/problems/intersection-of-two-arrays-ii
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        static constexpr int MXV = 1000;
        int cnt1[MXV+1]{};
        int cnt2[MXV+1]{};
        for (int n:nums1)
            cnt1[n]++;
        for (int n:nums2)
            cnt2[n]++;
        vector<int> ans;
        for (int n=0; n<=MXV; n++) {
            int c = min(cnt1[n], cnt2[n]);
            for (int i=0; i<c; i++)
                ans.push_back(n);
        }
        return ans;
    }
};
