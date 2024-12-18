// https://leetcode.com/problems/final-prices-with-a-special-discount-in-a-shop
class Solution
{
public:
    static vector<int> finalPrices(const vector<int>& prices)
    {
        int sz = prices.size();
        vector<int> pp;
        vector<int> res(sz);
        for (int i = sz - 1; i >= 0; i--)
        {
            while (!pp.empty() && pp.back() > prices[i])
            {
                pp.pop_back();
            }
            int gt = pp.empty() ? 0 : pp.back();
            res[i] = prices[i] - gt;
            if (gt != prices[i]) {
                pp.push_back(prices[i]);
            }
        }
        return res;
    }
};

