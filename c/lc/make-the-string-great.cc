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
