// https://leetcode.com/problems/sort-characters-by-frequency/
class Solution {
public:
    string frequencySort(const string &s) {
        int cnt[256]{0};
        for (unsigned char c:s)
            cnt[c]++;
        pair<int,char> srt[256];
        for (int c=0; c<256; c++)
            srt[c] = make_pair(cnt[c], c);
        sort(srt, srt+256);
        string ans;
        for (auto &s:srt)
            ans += string(s.first, s.second);
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
