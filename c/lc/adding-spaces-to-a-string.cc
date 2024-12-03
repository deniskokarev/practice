// https://leetcode.com/problems/adding-spaces-to-a-string
class Solution
{
public:
    static string addSpaces(const string& str, const vector<int>& sp)
    {
        auto str_sz = str.size();
        auto sp_sz = sp.size();
        string res(str_sz + sp.size(), ' ');
        int o = 0, i = 0, j = 0;
        while (i < str_sz)
        {
            if (j < sp_sz && i == sp[j])
            {
                o++, j++;
            }
            res[o++] = str[i++];
        }
        return res;
    }
};

