// https://leetcode.com/problems/last-stone-weight
class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        priority_queue<int> qq(begin(stones), end(stones));
        while (qq.size() > 1) {
            int b1 = qq.top();
            qq.pop();
            int b2 = qq.top();
            qq.pop();
            int d = abs(b1-b2);
            if (d) {
                qq.push(d);
            }
        }
        if (!qq.empty()) {
            return qq.top();
        } else {
            return 0;
        }
    }
};
