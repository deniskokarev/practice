class Solution {
public:
    vector<int> sortByBits(vector<int>& arr) {
        vector<pair<int,int>> ss;
        for (auto a:arr)
            ss.push_back({bitset<16>(a).count(), a});
        sort(ss.begin(), ss.end());
        vector<int> res;
        for (auto &p:ss)
            res.push_back(p.second);
        return res;
    }
};
