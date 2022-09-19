// https://leetcode.com/problems/trapping-rain-water/
#include <vector>
#include <numeric>
#include <iostream>

using namespace std;

class Solution {
public:
    static int trap(const vector<int> &hh) {
        unsigned sz = hh.size();
        unsigned aorig = accumulate(begin(hh), end(hh), 0U);
        unsigned a = 0;
        unsigned mx = 0;
        for (int i = 0; i < sz; i++) {
            mx = max(mx, unsigned(hh[i]));
            a += mx;
        }
        mx = 0;
        for (int i = sz - 1; i >= 0; i--) {
            mx = max(mx, unsigned(hh[i]));
            a += mx;
        }
        int ans = (a - (sz * mx)) - aorig;
        return ans;
    }
};

int main() {
    cout << Solution::trap({0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}) << endl;
    cout << Solution::trap({4,2,0,3,2,5}) << endl;
}
