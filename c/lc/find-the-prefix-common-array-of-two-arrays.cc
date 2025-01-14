// https://leetcode.com/problems/find-the-prefix-common-array-of-two-arrays
class Solution
{
public:
    static vector<int> findThePrefixCommonArray(const vector<int>& aa, const vector<int>& bb)
    {
        int sz = aa.size();
        bitset<64> ma{};
        bitset<64> mb{};
        vector<int> res(sz);
        int c = 0;
        for (int i = 0; i < sz; i++)
        {
            ma[aa[i]] = true;
            mb[bb[i]] = true;
            c += (mb[aa[i]]);
            c += (ma[bb[i]]);
            c -= (aa[i] == bb[i]);
            res[i] = c;
        }
        return res;
    }
};

