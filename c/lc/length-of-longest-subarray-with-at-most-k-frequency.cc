// https://leetcode.com/problems/length-of-longest-subarray-with-at-most-k-frequency
class Solution {
    struct S {
        // pp.front() is the leftmost pos for a number making
        // cnt=k if other numbers didn't matter
        deque<int> pp{-1};
        int cnt{};
    };
public:
    static int maxSubarrayLength(const vector<int> &nn, int k) {
        int sz = nn.size();
        unordered_map<int, S> n2s;
        int mx = 0;
        int span = 0; // max len subarray at pos i
        for (int i = 0; i < sz; i++) {
            S &s = n2s[nn[i]];
            // span=l if other numbers didn't matter
            int l = i - s.pp.front();
            s.pp.push_back(i);
            s.cnt++;
            if (s.cnt >= k) {
                s.pp.pop_front();
                s.cnt--;
            }
            // extend or snap to l
            if (l > span) {
                span++;
            } else {
                span = l;
            }
            mx = max(mx, span);
        }
        return mx;
    }
};

