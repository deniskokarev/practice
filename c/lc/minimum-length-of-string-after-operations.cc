// https://leetcode.com/problems/minimum-length-of-string-after-operations
class Solution
{
    // 0 -> 0
    // 1 -> 1
    // 2 -> 2
    // 3 * 1     -> 1
    // 4 = 3 * 1 + 1 -> 2
    // 5 = 3 * 1 + 2 -> 5 -> 3 -> 1
    // 6 = 3 * 2 -> 6 -> 4 -> 2
    static constexpr int ASZ = 'z' - 'a' + 1;

public:
    static int minimumLength(const string& s)
    {
        int cnt[ASZ]{};
        for (uint8_t c : s)
        {
            ++cnt[(c - 'a') % ASZ];
        }
        int ans = 0;
        for (int n : cnt)
        {
            if (n > 0)
            {
                ans += 2 - (n & 1);
            }
        }
        return ans;
    }
};
