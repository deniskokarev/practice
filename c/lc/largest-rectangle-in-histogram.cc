/**
       +
     +++
  ++++++.
++++++++.

  .......
.........
 */
class Solution {
    struct H {
        int x, y;
    };    
public:
    int largestRectangleArea(const vector<int>& heights) {
        int sz = heights.size();
        int mx = 0;
        vector<H> hh {{-1,-1}};
        for (int x=0; x<sz; x++) {
            int h = heights[x];
            int mnx = x;
            while (hh.back().y >= h) {
                mnx = hh.back().x;
                mx = max(mx, (x-mnx) * hh.back().y);
                hh.pop_back();
            }
            hh.push_back({mnx,h});
        }
        while (hh.back().y > 0) {
            mx = max(mx, (sz-hh.back().x) * hh.back().y);
            hh.pop_back();
        }
        return mx;
    }
};
