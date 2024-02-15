// https://leetcode.com/problems/find-polygon-with-the-largest-perimeter
class Solution {
public:
    long long largestPerimeter(vector<int>& nn) {
        int sz = nn.size();
        sort(begin(nn), end(nn));
        int64_t sm = nn[0] + nn[1];
        int64_t ans = -1;
        for (int i=2; i<sz; i++) {
            if (nn[i] < sm) {
                ans = sm + nn[i];
            }
            sm += nn[i];
        }
        return ans;
    }
};
