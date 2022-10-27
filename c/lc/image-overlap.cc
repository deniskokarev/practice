// https://leetcode.com/problems/image-overlap/
class Solution {
public:
    int largestOverlap(const vector<vector<int>>& img1, const vector<vector<int>>& img2) {
        int sz = img1.size();
        vector<int> i1(sz), i2(3*sz);
        for (int r=0; r<sz; r++) {
            int n1 = 0, n2 = 0;
            for (int b=0; b<sz; b++) {
                n1 <<= 1;
                n2 <<= 1;
                n1 |= img1[r][b];
                n2 |= img2[r][b];
            }
            i1[r] = n1;
            i2[r+sz] = n2;
        }
        int mx = 0;
        for (int y=0; y<sz*2; y++) {
            for (int s=0; s<sz; s++) {
                int cnt_l = 0;
                int cnt_r = 0;
                for (int r=0; r<sz; r++) {
                    auto n1 = i1[r];
                    auto n2_l = int64_t(i2[r+y]) << s;
                    auto n2_r = int64_t(i2[r+y]) >> s;
                    bitset<30> lm(int(n1 & n2_l));
                    bitset<30> rm(int(n1 & n2_r));
                    cnt_l += lm.count();
                    cnt_r += rm.count();
                }
                mx = max(mx, max(cnt_l, cnt_r));
            }
        }
        return mx;
    }
};
