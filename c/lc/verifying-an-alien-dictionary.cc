// https://leetcode.com/problems/verifying-an-alien-dictionary/
class Solution {
public:
    static bool isAlienSorted(vector<string>& words, const string &order) {
        int subst[26];
        for (int i=0; i<26; i++)
            subst[order[i]-'a'] = i;
        for (auto &w:words)
            for (auto &c:w)
                c = subst[c-'a'];
        int sz = words.size();
        bool ans = true;
        for (int i=0; i<sz-1; i++)
            ans &= (words[i] <= words[i+1]);
        return ans;
    }
};
