class Solution {
public:
    int largestAltitude(vector<int>& gain) {
        int sm = 0;
        int mx = sm;
        for (int g:gain) {
            sm += g;
            mx = max(mx, sm);
        }
        return mx;
    }
};
