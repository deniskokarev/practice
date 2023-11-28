// https://leetcode.com/problems/number-of-ways-to-divide-a-long-corridor
class Solution {
    static constexpr int MOD = 1e9 + 7;
public:
    static int numberOfWays(const string &cc) {
        uint64_t ans = 1;
        int sz = cc.size();
        int sc = 0;
        int l = -1;
        for (int i = 0; i < sz; i++) {
            if (cc[i] == 'S') {
                if ((sc & 1) == 0 && l >= 0) {
                    ans *= (i - l);
                    ans %= MOD;
                } else if ((sc & 1) == 1) {
                    l = i;
                }
                sc++;
            }
        }
        return (sc > 0 && (sc & 1) == 0) ? ans : 0;
    }
};

