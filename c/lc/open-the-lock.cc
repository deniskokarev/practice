// https://leetcode.com/problems/open-the-lock
class Solution {
    struct E {
        array<uint8_t, 4> s;

        int n() {
            int v = 0;
            for (auto &d: s) {
                d += 10;
                d %= 10;
                v *= 10;
                v += d;
            }
            return v;
        }
    };

public:
    static int openLock(const vector<string> &deadends, const string &target) {
        auto tgt = strtol(target.c_str(), nullptr, 10);
        vector<int> seen(10000, 0);
        for (auto &d: deadends) {
            auto n = strtol(d.c_str(), nullptr, 10);
            seen[n] = 1;
        }
        queue<E> qq;
        if (!seen[0]) {
            qq.push({0, 0, 0, 0});
            seen[0] = 1;
        }
        while (!qq.empty()) {
            auto top = qq.front();
            qq.pop();
            int tn = top.n();
            if (tn == tgt) {
                return seen[tn] - 1;
            }
            for (auto &d:top.s) {
                d++;
                int n = top.n();
                if (!seen[n]) {
                    seen[n] = seen[tn] + 1;
                    qq.push(top);
                }
                d -= 2;
                n = top.n();
                if (!seen[n]) {
                    seen[n] = seen[tn] + 1;
                    qq.push(top);
                }
                d++;
            }
        }
        return -1;
    }
};
