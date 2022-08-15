//https://leetcode.com/problems/roman-to-integer/
#include <iostream>
#include <vector>
#include <numeric>
#include <unordered_map>

using namespace std;

class Solution {
public:
    static int romanToInt(const string &s) {
        auto mm = unordered_map<char, int>({{'I', 1},
                                            {'V', 5},
                                            {'X', 10},
                                            {'L', 50},
                                            {'C', 100},
                                            {'D', 500},
                                            {'M', 1000}});
        int pd = 1001;
        int ans = 0;
        for (int c:s) {
            int d = mm[c];
            if (d > pd)
                ans -= 2 * pd;
            ans += d;
            pd = d;
        }
        return ans;
    }
};

int main(int argc, char **argv) {
    cout << Solution::romanToInt("MCMXCIV") << endl; // 1994
    return 0;
}
