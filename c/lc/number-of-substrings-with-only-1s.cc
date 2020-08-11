class Solution {
public:
    int numSub(const string &s) {
        constexpr int MOD = 1e9+7;
        int cnt=0;
        int ans = 0;
        for (char c:s) {
            cnt = (cnt+1)*(c=='1');
            ans += cnt;
            ans %= MOD;
        }
        return ans;
    }
};
