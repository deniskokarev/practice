#include <iostream>
#include <vector>
#include <array>
/* leetcode https://leetcode.com/problems/ones-and-zeroes/ */
using namespace std;

constexpr int MXSZ = 101;

class Solution {
    struct B {
        int bcnt[2];
    };

    static inline B cnt(const string &s) {
        B res{{0, 0}};
        for (auto c: s)
            res.bcnt[(c - '0') & 1]++;
        return res;
    }

public:
    static int findMaxForm(const vector <string> &strs, int m, int n) {
        // dp[ones][zeros] -> best solution on strs prefix with budget of so many ones/zeros
        int dp[MXSZ][MXSZ];
        memset(dp, 0, sizeof(dp));
        for (auto &s: strs) {
            auto rc = cnt(s);
            for (int bz = m; bz >= rc.bcnt[0]; bz--)
                for (int bo = n; bo >= rc.bcnt[1]; bo--)
                    dp[bz][bo] = max(dp[bz][bo], dp[bz - rc.bcnt[0]][bo - rc.bcnt[1]] + 1);
        }
        return dp[m][n];
    }
};

int main(int argc, char **argv) {
    cout << Solution::findMaxForm({"10", "0001", "111001", "1", "0"}, 5, 3) << endl;
    cout << Solution::findMaxForm({"10", "0", "1"}, 1, 1) << endl;
    return 0;
}
