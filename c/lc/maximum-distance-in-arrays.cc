// https://leetcode.com/problems/maximum-distance-in-arrays
class Solution {
public:
    int maxDistance(vector<vector<int>>& aa) {
        int sz = aa.size();
        int mn = aa[0][0], mx = aa[0].back();
        int ans = 0;
        for (int i=1; i<sz; i++) {
            auto &a = aa[i];
            int n = a[0];
            int x = a.back();
            ans = max({ans, abs(mn - n), abs(mn - x), abs(mx - n), abs(mx - x)});
            mn = min(mn, n);
            mx = max(mx, x);
        }
        return ans;
    }
};
