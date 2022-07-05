// https://leetcode.com/problems/longest-consecutive-sequence/
class Solution {
public:
    static int longestConsecutive(const vector<int> &nums) {
        unordered_set<int> seq; // interval start -> p2 size
        for (auto n: nums)
            seq.insert(n);
        int mx = 0;
        for (auto n: nums) {
            int i = n;
            int cnt = 0;
            auto fnd = seq.find(i);
            while (fnd != seq.end()) {
                cnt++;
                i--;
                seq.erase(fnd);
                fnd = seq.find(i);
            }
            i = n + 1;
            fnd = seq.find(i);
            while (fnd != seq.end()) {
                cnt++;
                i++;
                seq.erase(fnd);
                fnd = seq.find(i);
            }
            mx = max(mx, cnt);
        }
        return mx;
    }
};
