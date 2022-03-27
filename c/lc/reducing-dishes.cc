// https://leetcode.com/problems/reducing-dishes/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution2 {
public:
    static int maxSatisfaction(const vector<int> &sat) {
        int sz = sat.size();
        vector<int> ss(sat); // sorted sequence
        sort(ss.begin(), ss.end());
        // dp[i][l] - best cost of taking some l elements from first i elements
        // must initialize with -Inf since we must consider going into negative
        vector<vector<int>> dp(sz + 1, vector<int>(sz + 1, INT_MIN));
        // but taking no elements should always be 0
        for (int i = 0; i <= sz; i++)
            dp[i][0] = 0;
        for (int i = 1; i <= sz; i++)
            for (int l = 1; l <= i; l++)
                dp[i][l] = max(dp[i - 1][l], dp[i - 1][l - 1] + ss[i - 1] * l);
        return *max_element(dp[sz].begin(), dp[sz].end());
    }
};

class Solution {
public:
    static int maxSatisfaction(const vector<int> &sat) {
        int sz = sat.size();
        vector<int> ss(sat); // sorted sequence in desc order
        sort(ss.begin(), ss.end(), greater<int>());
        // if it was sorted in asc order we'd go from right to left
        // and take entire positive part,
        // then we can go into negative part while the total sum increases
        int mx = 0;
        int tot = 0;
        int sm = 0;
        for (auto n:ss) {
            sm += n;
            tot += sm;
            mx = max(mx, tot);
        }
        return mx;
    }
};

int main(int argc, char **argv) {
    cout << Solution::maxSatisfaction({-1, -8, 0, 5, -9}) << endl;
    cout << Solution::maxSatisfaction({4, 3, 2}) << endl;
    cout << Solution::maxSatisfaction({-1, -4, -5}) << endl;
    return 0;
}
