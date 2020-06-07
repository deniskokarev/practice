// https://leetcode.com/problems/coin-change-2/
class Solution {
public:
    int change(int amount, const vector<int>& coins) {
        if (coins.size() < 1) {
            if (amount == 0)
                return 1;
            else
                return 0; // f..ers
        }
        int mxc = *max_element(coins.begin(), coins.end());
        vector<int> amt(amount+1+mxc);
        amt[0] = 1;
        for (const int &c:coins)
            for (int a=0; a<amount; a++)
                amt[a+c] += amt[a];
        return amt[amount];
    }
};
