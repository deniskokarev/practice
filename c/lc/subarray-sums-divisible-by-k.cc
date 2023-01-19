// https://leetcode.com/problems/subarray-sums-divisible-by-k/
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    static int subarraysDivByK(const vector<int> &nums, int k) {
        vector<int> mcnt(k);
        mcnt[0] = 1;
        int ans = 0;
        int sm = 0;
        for (auto n: nums) {
            sm += n;
            int r;
            if (sm < 0) {
                r = (k + (sm % k)) % k;
            } else {
                r = sm % k;
            }
            ans += mcnt[r];
            mcnt[r]++;
        }
        return ans;
    }
};

int main(int argc, char **argv) {
    cout << Solution::subarraysDivByK({-5}, 5) << endl;
    cout << Solution::subarraysDivByK({4, 5, 0, -2, -3, 1}, 5) << endl;
    return 0;
}

