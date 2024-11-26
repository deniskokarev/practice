// https://leetcode.com/problems/find-champion-ii
class Solution
{
    using G = vector<vector<int>>;

    static int get_parent(vector<int>& res, int n, const G& par)
    {
        if (res[n] > 0)
        {
            return res[n];
        }
        if (par[n].empty())
        {
            return res[n] = n + 1;
        }
        return res[n] = get_parent(res, par[n][0], par);
    }

public:
    static int findChampion(int n, const vector<vector<int>>& edges)
    {
        G par(n);
        for (const auto& e : edges)
        {
            par[e[1]].push_back(e[0]);
        }
        vector<int> champion(n);
        for (int i = 0; i < n; i++)
        {
            champion[i] = get_parent(champion, i, par);
        }
        for (int i = 1; i < n; i++)
        {
            if (champion[i] != champion[i - 1])
            {
                return -1;
            }
        }
        return champion[0] - 1;
    }
};
