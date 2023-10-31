// https://leetcode.com/problems/find-the-original-array-of-prefix-xor/
class Solution {
public:
    vector<int> findArray(vector<int> &pref) {
        int sz = pref.size();
        int x = pref[0];
        for (int i = 1; i < sz; i++) {
            int px = x;
            x = pref[i];
            pref[i] ^= px;
        }
        return pref;
    }
};
