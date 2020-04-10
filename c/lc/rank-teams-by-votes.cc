class Solution {
    using K = array<int,26>;
public:
    string rankTeams(vector<string>& votes) {
        int MX = 26;
        int sz = votes[0].size();
        vector<pair<K,int>> teams(MX);
        for (int i=0; i<MX; i++)
            teams[i] = {{{0}}, -i};
        for (const string &v:votes) {
            for (int place=0; place<sz; place++)
                teams[v[place]-'A'].first[place]++;
        }
        sort(teams.begin(), teams.end(), std::greater<pair<K,char>>());
        string ans(sz, ' ');
        for (int i=0; i<sz; i++)
            ans[i] = 'A' - teams[i].second;
        return ans;
    }
};
