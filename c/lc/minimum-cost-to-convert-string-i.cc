// https://leetcode.com/problems/minimum-cost-to-convert-string-i
class Solution {
    static constexpr int DIM = 'z' - 'a' + 1;
    using M = array<array<int, DIM>, DIM>;
    static constexpr int INF = INT_MAX / 2;

    static void floyd(M &mm) {
        for (int k = 0; k < DIM; k++) {
            for (int i = 0; i < DIM; i++) {
                for (int j = 0; j < DIM; j++) {
                    mm[i][j] = min(mm[i][j], mm[i][k] + mm[k][j]);
                }
            }
        }
    }

public:
    static long long minimumCost(const string &source, const string &target, const vector<char> &original,
                                 const vector<char> &changed,
                                 const vector<int> &cost) {
        M mm;
        for (int i = 0; i < DIM; i++) {
            fill(mm[i].begin(), mm[i].end(), INF);
        }
        for (int i = 0; i < DIM; i++) {
            mm[i][i] = 0;
        }
        for (int i = 0; i < original.size(); i++) {
            const int f = (original[i] - 'a') % DIM;
            const int t = (changed[i] - 'a') % DIM;
            mm[f][t] = min(mm[f][t], cost[i]);
        }
        floyd(mm);
        int64_t ans = 0;
        for (int i = 0; i < source.size(); i++) {
            const int f = (source[i] - 'a') % DIM;
            const int t = (target[i] - 'a') % DIM;
            if (mm[f][t] == INF) {
                return -1;
            }
            ans += mm[f][t];
        }
        return ans;
    }
};

