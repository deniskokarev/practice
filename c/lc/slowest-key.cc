// https://leetcode.com/contest/weekly-contest-212/problems/slowest-key/
class Solution {
public:
    char slowestKey(vector<int>& releaseTimes, string keysPressed) {
        int sz = releaseTimes.size();
        vector<pair<int,char>> res(sz);
        res[0] = {releaseTimes[0], keysPressed[0]};
        for (int i=1; i<sz; i++)
            res[i] = {releaseTimes[i] - releaseTimes[i-1], keysPressed[i]};
        sort(res.begin(), res.end());
        return res[sz-1].second; 
    }
};
