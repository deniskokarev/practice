class Solution {
public:
    int countGoodRectangles(vector<vector<int>>& recs) {
        int mx = INT_MIN;
        for (auto &r:recs)
            mx = max(mx, min(r[0], r[1]));
        int cnt = 0;
        for (auto &r:recs) {
            int mn = min(r[0], r[1]);
            cnt += (mn == mx);
        }
        return cnt;
    }
};
