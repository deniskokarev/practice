class Solution {
public:
    int findLucky(vector<int>& arr) {
        map<int,int> cnt;
        for (auto a:arr)
            cnt[a]++;
        int ans = -1;
        for (auto it=cnt.begin(); it!=cnt.end(); ++it)
            if (it->first == it->second)
                ans = it->first;
        return ans;
    }
};
