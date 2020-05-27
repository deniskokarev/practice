/**
 * https://leetcode.com/problems/single-element-in-a-sorted-array/
 */
class Solution {
public:
    int singleNonDuplicate(const vector<int>& nn) {
        int f=0, t=nn.size();
        while (f+1 < t) {
            int m=(t+f)/2;
            if (m&1) {
                if (nn[m] == nn[m+1])
                    t = m;
                else
                    f = m+1;
            } else {
                if (nn[m] == nn[m+1])
                    f = m+2;
                else
                    t = m;
            }
        }
        return nn[f];
    }
};
