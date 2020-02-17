#include <vector>
using namespace std;
/* https://leetcode.com/contest/weekly-contest-130/problems/binary-prefix-divisible-by-5 */

class Solution {
public:
    vector<bool> prefixesDivBy5(vector<int>& A) {
        int sz = A.size();
        vector<bool> res(sz);
        int r5 = 0;
        for (int i=0; i<sz; i++) {
            r5 = r5+r5 + A[i];
            r5 %= 5;
            res[i] = (r5 == 0);
        }
        return res;
    }
};
