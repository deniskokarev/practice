class Solution {
public:
    int maxWidthOfVerticalArea(vector<vector<int>>& points) {
        int sz = points.size();
        vector<int> xx(sz);
        for (int i=0; i<sz; i++)
            xx[i] = points[i][0];
        sort(xx.begin(), xx.end());
        int mx = 0;
        for (int i=1; i<sz; i++)
            mx = max(mx, xx[i] - xx[i-1]);
        return mx;
    }
};
