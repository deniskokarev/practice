// https://leetcode.com/problems/minimized-maximum-of-products-distributed-to-any-store
class Solution
{
    static bool can_place(int n, const vector<int>& qq, int upto)
    {
        for (int q : qq)
        {
            while (n > 0 && q > 0)
            {
                q -= upto;
                n--;
            }
            if (n == 0 && q > 0)
            {
                return false;
            }
        }
        return true;
    }

public:
    static int minimizedMaximum(int n, const vector<int>& qq)
    {
        int f = 0, t = 1e5 + 1;
        while (f < t)
        {
            int m = (f + t) / 2;
            if (can_place(n, qq, m))
            {
                t = m;
            }
            else
            {
                f = m + 1;
            }
        }
        return f;
    }
};
