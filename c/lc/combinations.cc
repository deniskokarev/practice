// https://leetcode.com/problems/combinations/
class Solution {
    static void comb(vector<vector<int>> &res, int *vv, int *p, int b, int e, int rem) {
        if (rem) {
            for (int i = b; i < e; i++) {
                *p = i;
                comb(res, vv, (p + 1), i + 1, e, rem - 1);
            }
        } else {
            res.push_back({vv, p});
        }
    }

public:
    static vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;
        int vv[k];
        comb(res, vv, vv, 1, n + 1, k);
        return res;
    }
};

