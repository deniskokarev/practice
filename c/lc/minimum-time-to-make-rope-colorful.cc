// https://leetcode.com/problems/minimum-time-to-make-rope-colorful/
using T = struct {
    char c;
    int cost;
};

class Solution {
public:
    static int minCost(const string &col, const vector<int>& cost) {
        vector<T> stack;
        int i = 0;
        T last {'-', 0};
        int ans = 0;
        for (auto &c:col) {
            T curr { col[i], cost[i] };
            if (last.c == curr.c) {
                if (curr.cost > last.cost) {
                    ans += last.cost;
                    last = curr;
                } else {
                    ans += curr.cost;                    
                }
            } else {
                last = curr;
            }
            i++;
        }
        return ans;
    }
};
