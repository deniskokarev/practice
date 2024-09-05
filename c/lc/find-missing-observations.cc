// https://leetcode.com/problems/find-missing-observations
class Solution {
    static bool splice(vector<int> &res, int d) {
        int n = res.size();
        if (d < n || d > 6 * n) {
            return false;
        }
        for (int i = 0, l = n; i < n; i++, l--) {
            int v = (d + l - 1) / l;
            res[i] = v;
            d -= v;
        }
        return true;
    }

public:
    static vector<int> missingRolls(const vector<int> &rolls, int mean, int n) {
        int m = rolls.size();
        int sm = accumulate(rolls.begin(), rolls.end(), 0);
        int d = mean * (m + n) - sm;
        vector<int> res(n, 0);
        if (splice(res, d)) {
            return res;
        } else {
            return {};
        }
    }
};
