// https://leetcode.com/problems/kids-with-the-greatest-number-of-candies
class Solution {
public:
    static vector<bool> kidsWithCandies(const vector<int>& candies, int extraCandies) {
        int sz = candies.size();
        int mx = *max_element(begin(candies), end(candies));
        vector<bool> ans(sz);
        for (int i=0; i<sz; i++)
            ans[i] = (candies[i] + extraCandies) >= mx;
        return ans;
    }
};
