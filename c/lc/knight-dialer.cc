// https://leetcode.com/problems/knight-dialer/
class Solution {
    static constexpr unsigned MOD = 1e9 + 7;
public:
    static int knightDialer(int n) {
        static const vector<vector<int>> MV = {{4, 6},
                                               {6, 8},
                                               {7, 9},
                                               {4, 8},
                                               {0, 3, 9},
                                               {},
                                               {0, 1, 7},
                                               {2, 6},
                                               {1, 3},
                                               {2, 4}};
        array<array<unsigned, 10>, 2> aa;
        int s = 0;
        fill(begin(aa[s]), end(aa[s]), 1);
        while (--n) {
            int n = !s;
            fill(begin(aa[n]), end(aa[n]), 0);
            for (int i = 0; i < aa[0].size(); i++) {
                aa[s][i] %= MOD;
                for (auto m: MV[i]) {
                    aa[n][m] += aa[s][i];
                }
            }
            s = n;
        }
        uint64_t ans = accumulate(begin(aa[s]), end(aa[s]), 0UL);
        return ans % MOD;
    }
};

