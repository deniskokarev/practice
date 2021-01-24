class Solution {
public:
    static int countPairs(const vector<int>& del) {
        constexpr int MOD = 1e9+7;
        unordered_map<int,int> cnt(1e6+3);
        uint64_t sm = 0;
        for (auto d:del) {
            for (uint64_t l2=0,p2=1; l2<22; l2++,p2<<=1) {
                sm += cnt[p2-d];
                sm %= MOD;
            }            
			cnt[d]++;
        }
        return sm;
    }
};
