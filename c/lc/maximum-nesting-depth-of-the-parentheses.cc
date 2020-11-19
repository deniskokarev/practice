class Solution {
public:
    int maxDepth(const string &s) {
        int dep = 0;
        int mx = 0;
        for (auto c:s) {
            if (c == '(')
                dep++;
            else if (c == ')')
                dep--;
            mx = max(mx, dep);
        }
        return mx;
    }
};
