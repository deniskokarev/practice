// https://leetcode.com/problems/validate-stack-sequences
class Solution {
    static bool
    validateStackSequences(const vector<int> &pushed, const vector<int> &popped,
                           const int v2p[], int i, int j, int sz) {
        if (sz == 0) {
            return true;
        } else {
            int l = v2p[pushed[i]] - j;
            return
                    l > 0
                    && l <= sz
                    && validateStackSequences(pushed, popped, v2p, i + 1, j, l - 1)
                    && validateStackSequences(pushed, popped, v2p, i + l, j + l, sz - l);
        }
    }
public:
    static bool validateStackSequences(const vector<int> &pushed, const vector<int> &popped) {
        int sz = pushed.size();
        int v2p[1001]{};
        for (int p = 0; p < sz; p++)
            v2p[popped[p]] = p + 1;
        return validateStackSequences(pushed, popped, v2p, 0, 0, sz);
    }
};
