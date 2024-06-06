// https://leetcode.com/problems/hand-of-straights
class Solution {
public:
    bool isNStraightHand(const vector<int> &hand, int gsz) {
        multiset<int> ss;
        for (auto n: hand) {
            ss.insert(n);
        }
        while (!ss.empty()) {
            int f = *begin(ss);
            for (int i = f; i < f + gsz; i++) {
                auto fnd = ss.find(i);
                if (fnd != ss.end()) {
                    ss.erase(fnd);
                } else {
                    return false;
                }
            }
        }
        return true;
    }
};

