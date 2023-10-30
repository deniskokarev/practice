// https://leetcode.com/problems/sort-integers-by-the-number-of-1-bits
class Solution {
    static inline bool lt(int a, int b) {
        bitset<16> ma(a), mb(b);
        int ca = ma.count(), cb = mb.count();
        return ca < cb || ca == cb && a < b;
    }

public:
    static vector<int> sortByBits(vector<int> &arr) {
        sort(begin(arr), end(arr), lt);
        return arr;
    }
};

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
