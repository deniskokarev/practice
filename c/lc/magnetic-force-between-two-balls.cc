class Solution {
    bool may_fit(const vector<int>& position, int m, int dist) {
        int sz = position.size();
        int place = position[0];
        m--;
        for (int i=1; i<sz; i++) {
            if (position[i] - place >= dist) {
                place = position[i];
                m--;
            }
        }
        return (m<=0);
    }
public:
    int maxDistance(vector<int>& position, int m) {
        constexpr int INF = INT_MAX;
        sort(position.begin(), position.end());
        int f=1, t=INF;
        while (f<=t) {
            int mid = f+(t-f)/2;
            if (may_fit(position, m, mid))
                f = mid+1;
            else
                t = mid-1;
        }
        return f-1;
    }
};
