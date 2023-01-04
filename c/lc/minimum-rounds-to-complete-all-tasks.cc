// https://leetcode.com/problems/minimum-rounds-to-complete-all-tasks/
class Solution {
    int steps(int n) {
        if (n < 2)
            return -1;
        int ans = n / 3;
        int r = n % 3;
        if (r != 0)
            ans++;
        return ans;
    }
public:
    int minimumRounds(const vector<int>& tasks) {
        unordered_map<int,int> cnt;
        for (int t: tasks)
            cnt[t]++;
        int ans = 0;
        for (auto kv:cnt) {
            int st = steps(kv.second);
            if (st == -1)
                return -1;
            ans += st;
        }
        return ans;
    }
};
