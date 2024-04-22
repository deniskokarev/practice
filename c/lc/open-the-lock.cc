// https://leetcode.com/problems/open-the-lock
class Solution {
    struct E {
        array<uint8_t, 4> s;
        int n;

        void s2n() {
            n = 0;
            for (auto &d: s) {
                d += 10;
                d %= 10;
                n *= 10;
                n += d;
            }
        }
    };

public:
    static int openLock(const vector<string> &deadends, const string &target) {
        vector<int> seen(10000, 0);
        for (auto &d: deadends) {
            auto n = strtol(d.c_str(), nullptr, 10);
            seen[n] = 1;
        }
        auto tgt = strtol(target.c_str(), nullptr, 10);
        queue<E> qq;
        if (!seen[0]) {
            qq.push({{0, 0, 0, 0}, 0});
            seen[0] = 1;
        }
        while (!qq.empty()) {
            auto top = qq.front();
            qq.pop();
            if (top.n == tgt) {
                return seen[top.n] - 1;
            }
            for (int p = 0; p < top.s.size(); p++) {
                E e(top);
                e.s[p]++;
                e.s2n();
                if (!seen[e.n]) {
                    seen[e.n] = seen[top.n] + 1;
                    qq.push(e);
                }
                e.s[p] -= 2;
                e.s2n();
                if (!seen[e.n]) {
                    seen[e.n] = seen[top.n] + 1;
                    qq.push(e);
                }
            }
        }
        return -1;
    }
};

