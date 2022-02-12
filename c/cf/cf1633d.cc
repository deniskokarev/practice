#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
/* CodeForces CF1633D problem */
using namespace std;

const int MX_B = 1000;

// build minimal distance from 1 to each b
vector<int> build_dist(int sz) {
    vector<int> dist(sz, -1);
    dist[1] = 0;
    deque<int> wave;
    wave.push_back(1);
    while (!wave.empty()) {
        int p = wave.front();
        wave.pop_front();
        for (int i = 1; i <= p; i++) {
            int np = p + p / i;
            if (np < sz && dist[np] == -1) {
                dist[np] = dist[p] + 1;
                wave.push_back(np);
            }
        }
    }
    return dist;
}

int knapsack(const vector<int> &c, const vector<int> &w, int tot_w) {
    int sz = c.size();
    vector<vector<int>> dp(tot_w + 1, vector<int>(sz));
    for (int tw = 0; tw <= tot_w; tw++) {
        if (w[0] <= tw)
            dp[tw][0] = c[0];
        for (int i = 1; i < sz; i++) {
            dp[tw][i] = dp[tw][i - 1];
            if (w[i] <= tw)
                dp[tw][i] = max(dp[tw][i], dp[tw - w[i]][i - 1] + c[i]);
        }
    }
    return dp[tot_w][sz - 1];
}

int main(int argc, char **argv) {
    auto dist = build_dist(MX_B + 1);
    int mx_dist = *max_element(dist.begin(), dist.end()); // 12 for 1000
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> bb(n);
        for (auto &b:bb)
            cin >> b;
        vector<int> cc(n);
        for (auto &c:cc)
            cin >> c;
        vector<int> ww(n);
        for (int i = 0; i < n; i++)
            ww[i] = dist[bb[i]];
        // no need to go to very large k
        int ans = knapsack(cc, ww, min(k, mx_dist * n));
        cout << ans << '\n';
    }
    return 0;
}
