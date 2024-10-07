// https://leetcode.com/problems/minimum-string-length-after-removing-substrings
class Solution {
public:
    static int minLength(const string& s) {
        string t;
        static const array<pair<char, char>, 2> mm{{{'A', 'B'}, {'C', 'D'}}};
        for (auto c : s) {
            for (auto& p : mm) {
                if (c == p.second && !t.empty() && t.back() == p.first) {
                    t.pop_back();
                    goto next;
                }
            }
            t.push_back(c);
        next:
        }
        return t.size();
    }
};
