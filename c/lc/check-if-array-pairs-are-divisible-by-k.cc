// https://leetcode.com/problems/check-if-array-pairs-are-divisible-by-k
class Solution
{
public:
    static bool canArrange(const vector<int>& arr, const int k)
    {
        int tot = 0;
        vector<int> rem(k);
        for (const int a : arr)
        {
            const int p = (a % k + k) % k;
            const int mp = (k - p) % k;
            int& r = rem[p];
            int& mr = rem[mp];
            if (mr > 0)
            {
                mr--;
                tot--;
            }
            else
            {
                r++;
                tot++;
            }
        }
        return tot == 0;
    }
};

