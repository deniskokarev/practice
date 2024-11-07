// https://leetcode.com/problems/largest-combination-with-bitwise-and-greater-than-zero
class Solution
{
public:
    static inline int largestCombination(const vector<int>& nn)
    {
        int mx = 0;
        for (int b = 0, m = 1; b < 25; b++, m <<= 1)
        {
            int cnt = accumulate(nn.begin(), nn.end(), 0, [&](int acc, int n) { return acc + (n & m ? 1 : 0); });
            mx = max(mx, cnt);
        }
        return mx;
    }
};

