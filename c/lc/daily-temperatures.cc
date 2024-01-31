// https://leetcode.com/problems/daily-temperatures
class Solution {
public:
    static vector<int> dailyTemperatures(const vector<int> &tt) {
        vector<int> ans(tt.size());
        set<pair<int, int>> rr;
        rr.insert({INT_MAX, 0});
        for (int i = tt.size() - 1; i >= 0; i--) {
            auto fnd = rr.upper_bound({tt[i], INT_MAX});
            ans[i] = max(0, fnd->second - i);
            auto it = begin(rr);
            while (it != fnd) {
                auto nxt = next(it);
                rr.erase(it);
                it = nxt;
            }
            rr.insert({tt[i], i});
        }
        return ans;
    }
};
