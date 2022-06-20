// https://leetcode.com/problems/short-encoding-of-words/

constexpr int MXSZ = 26;

class Solution {
    struct T {
        int nxt[MXSZ]{0};
        bool is_leaf{true};
        int dep{0};
    };
public:
    static int minimumLengthEncoding(const vector<string> &words) {
        vector<T> tt(2);
        for (auto &w: words) {
            int r = 1;
            int dep = 1;
            int wsz = w.size();
            for (int i = wsz-1; i>=0; i--) {
                char ch = w[i];
                int idx = int(ch - 'a') % MXSZ;
                if (tt[r].nxt[idx] == 0) {
                    tt[r].nxt[idx] = tt.size();
                    tt.push_back(T{});
                    tt[r].is_leaf = false;
                }
                r = tt[r].nxt[idx];
                tt[r].dep = dep + 1;
                dep++;
            }
        }
        int ans = 0;
        for (auto &t: tt) {
            if (t.is_leaf) {
                ans += t.dep;
            }
        }
        return ans;
    }
};

