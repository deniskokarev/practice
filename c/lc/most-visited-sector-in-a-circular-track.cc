class Solution {
public:
    vector<int> mostVisited(int n, vector<int>& rounds) {
        vector<pair<int,int>> sect(n);
        int j = 0;
        for (auto &s:sect)
            s.second = j++;
        int sz = rounds.size();
        for (int i=0; i<sz-1; i++) {
            j = rounds[i]-1;
            while (j != rounds[i+1]-1) {
                sect[j].first++;
                j++;
                j %= n;
            }
        }
        sect[j].first++;
        sort(sect.begin(), sect.end());
        vector<int> res;
        res.push_back(sect[n-1].second+1);
        for (int i=n-2; i>=0 && sect[i].first == sect[i+1].first; i--)
            res.push_back(sect[i].second+1);
        reverse(res.begin(), res.end());
        return res;
    }
};
