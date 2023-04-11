// https://leetcode.com/problems/removing-stars-from-a-string/
class Solution {
public:
    static string removeStars(const string &s) {
        string o;
        for (auto c:s) {
            if (c == '*') {
                if (!o.empty())
                    o.pop_back();
            } else {
                o.push_back(c);
            }
        }
        return o;
    }
};
