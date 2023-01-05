// https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons
class Solution {
    struct S {
        int x;
        int d;
        int id;
        bool operator<(const S &o) const {
            return x < o.x || x == o.x && d < o.d;
        }
    };
public:
    static int findMinArrowShots(const vector<vector<int>>& points) {
        vector<S> ss;
        unordered_set<int> del;
        int id = 0;
        for (auto &p:points) {
            ss.push_back({p[0], -1, id});
            ss.push_back({p[1], +1, id});
            id++;
        }
        sort(ss.begin(), ss.end());
        int d = 0;
        int ans = 0;
        unordered_set<int> curr;
        for (auto &s:ss) {
            if (s.d < 0) {
                curr.insert(s.id);
            } else if (s.d > 0 && del.find(s.id) == del.end()) {
                del.insert(curr.begin(), curr.end());
                ans++;
                curr = {};
            }
        }
        return ans;
    }
};
