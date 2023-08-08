// https://leetcode.com/problems/search-in-rotated-sorted-array/
class Solution {
    static int pivot(const vector<int> &nn) {
        int sz = nn.size();
        int f = 1, t = sz;
        while (f < t) {
            int m = f + (t - f) / 2;
            if (nn[0] >= nn[m]) {
                t = m;
            } else {
                f = m + 1;
            }
        }
        return f;
    }

public:
    static int search(const vector<int> &nn, int k) {
        int sz = nn.size();
        int m = pivot(nn);
        int p1 = lower_bound(begin(nn), begin(nn) + m, k) - begin(nn);
        if (p1 < m && p1 < sz && nn[p1] == k) {
            return p1;
        } else {
            int p2 = lower_bound(begin(nn) + m, begin(nn) + sz, k) - begin(nn);
            if (p2 < sz && nn[p2] == k) {
                return p2;
            } else {
                return -1;
            }
        }
    }
};

