class Solution {
    static constexpr int MXR = 16;
public:
    int maximumRequests(int n, vector<vector<int>>& req) {
        int sz = req.size();
        size_t mx = 0;
        for (int i=0; i<(1<<sz); i++) {
            vector<int> sm(n);
            bitset<MXR> bb(i);
            for (int j=0; j<sz; j++) {
                if (bb[j]) {
                    sm[req[j][0]]--;
                    sm[req[j][1]]++;
                }
            }
            int all0 = true;
            for (int j=0; j<n; j++)
                all0 &= (sm[j] == 0);
            if (all0)
                mx = max(mx, bb.count());
        }
        return mx;
    }
};
