// https://leetcode.com/problems/first-unique-character-in-a-string/
class Solution {
    struct E {
        int p, b;
    };
public:
    static int firstUniqChar(const string &s) {
        int sz = s.size();
        array<int, 27> cnt{0};
        array<E, 27> stack;
        int top = 0;
        stack[top++] = {-1, 26};
        for (int p = sz - 1; p >= 0; p--) {
            int b = s[p] - 'a';
            if (cnt[b] == 0) {
                stack[top++] = {p, b};
            }
            cnt[b]++;
        }
        top--;
        while (cnt[stack[top].b] > 1) {
            top--;
        }
        return stack[top].p;
    }
};

