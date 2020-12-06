class Solution {
public:
    string interpret(const string &command) {
        string a(command);
        string b;
        int sz = command.size();
        int p;
        for (p=1; p<sz; p++) {
            if (a[p-1]=='(' && a[p] == ')') {
                b.push_back('o');
                p++;
            } else {
                b.push_back(a[p-1]);
            }
        }
        if (p == sz)
            b.push_back(a[p-1]);
        a = b;
        sz = a.size();
        b = "";
        for (char c:a)
            if (c != '(' && c != ')')
                b.push_back(c);
        return b;
    }
};
