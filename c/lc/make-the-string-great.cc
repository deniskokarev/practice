// https://leetcode.com/problems/make-the-string-great/

constexpr char UC = 1 << 5;

class Solution {
public:
    static string makeGood(const string &s) {
        string ss;
        ss.push_back(' ');
        for (auto c:s) {
            char p = ss.back();
            if ((c ^ p) == UC)
                ss.pop_back();
            else
                ss.push_back(c);
        }
        return ss.substr(1);
    }
};

class Solution {
public:
    string makeGood(const string &s) {
        stack<char> stack;
        for (char c:s) {
            if (!stack.empty() && stack.top() == (c^32))
                stack.pop();
            else
                stack.push(c);
        }
        int sz = stack.size();
        string res(sz, ' ');
        for (int i=sz-1; i>=0; i--) {
            res[i] = stack.top();
            stack.pop();
        }
        return res;
    }
}
