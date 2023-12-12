// https://leetcode.com/problems/element-appearing-more-than-25-in-sorted-array
class Solution {
public:
    static int findSpecialInteger(const vector<int> &nn) {
        int sz = nn.size();
        int q = sz / 4;
        int i = 0;
        while (i + q < sz) {
            if (nn[i] == nn[i + q]) {
                return nn[i];
            } else {
                i = lower_bound(nn.begin() + i + 1, nn.begin() + i + q + 1, nn[i + q]) - nn.begin();
            }
        }
        return nn[sz - 1];
    }
};
