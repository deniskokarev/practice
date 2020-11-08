class Solution {
public:
    int getMaximumGenerated(int n) {
        vector<int> res(n+2);
        res[0] = 0;
        res[1] = 1;
        int mx = 0;
        for (int i=1; i<=n; i++) {
            if (i&1)
                res[i] = res[i/2]+res[i/2+1];
            else
                res[i] = res[i/2];
            mx = max(mx, res[i]);
        }
        return mx;
    }
};
