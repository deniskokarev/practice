// https://leetcode.com/problems/rectangle-area/
class Solution {
public:
    int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2) {
        int l = max(ax1, bx1);    
        int r = min(ax2, bx2);
        int b = max(ay1, by1);
        int t = min(ay2, by2);
        int w = r - l;
        int h = t - b;
        int oa = 0;
        if (w > 0 && h > 0)
            oa = w * h;
        int ah = ay2 - ay1;
        int aw = ax2 - ax1;
        int bh = by2 - by1;
        int bw = bx2 - bx1;
        return  ah * aw + bh * bw - oa;
    }
};
