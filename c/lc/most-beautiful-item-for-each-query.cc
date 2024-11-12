// https://leetcode.com/problems/most-beautiful-item-for-each-query
class Solution
{
    struct E
    {
        int p, b;

        bool operator<(const E& e) const
        {
            return p < e.p;
        }
    };

public:
    static vector<int> maximumBeauty(const vector<vector<int>>& items, const vector<int>& queries)
    {
        int sz = items.size();
        vector<E> pb(sz);
        for (int i = 0; i < sz; i++)
        {
            pb[i] = {.p = items[i][0], .b = items[i][1]};
        }
        sort(begin(pb), end(pb));
        for (int i = 1; i < sz; i++)
        {
            pb[i].b = max(pb[i].b, pb[i - 1].b);
        }
        vector<int> ans(queries.size(), 0);
        for (int i = 0; i < queries.size(); i++)
        {
            int pos = upper_bound(begin(pb), end(pb), E{.p = queries[i]}) - begin(pb);
            if (pos > 0)
                ans[i] = pb[pos - 1].b;
        }
        return ans;
    }
};

