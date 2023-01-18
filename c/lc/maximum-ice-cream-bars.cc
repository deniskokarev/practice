// https://leetcode.com/problems/maximum-ice-cream-bars/
class Solution {
public:
    int maxIceCream(vector<int>& costs, int coins) {
        int sz = costs.size();
        sort(costs.begin(), costs.end());
        int i = 0;
        int sm = 0;
        while (i < sz && sm <= coins) {
            sm += costs[i++];
        }
        return i - (sm > coins);
    }
};
