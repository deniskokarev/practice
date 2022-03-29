// https://leetcode.com/problems/unique-paths-iii/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
private:
    struct P {
        int r, c;
    };

    struct M {
        // seen_nodes_mask -> count_paths
        // at the peak seen_nodes set will be size of binomial(10,20) ~ 185K
        unordered_map<int, int> seen_cnt;
    };

    static inline int node_msk(int w, const P &p) {
        return 1 << (p.r * w + p.c);
    }

    static vector<vector<M>> one_bfs_step(const vector<vector<M>> &bfs) {
        const int h = bfs.size();
        const int w = bfs[0].size();
        vector<vector<M>> res(h, vector<M>(w));
        for (int r = 0; r < h; r++) {
            for (int c = 0; c < w; c++) {
                for (const auto &p:(const P[]) {P{1, 0}, P{0, 1}, P{-1, 0}, P{0, -1}}) {
                    const P np = P{r + p.r, c + p.c};
                    if (np.r >= 0 && np.r < h && np.c >= 0 && np.c < w) {
                        const int np_msk = node_msk(w, np);
                        for (auto &seen_cnt:bfs[r][c].seen_cnt) {
                            const int seen_msk = seen_cnt.first;
                            const int cnt = seen_cnt.second;
                            if (!(seen_msk & np_msk)) {
                                res[np.r][np.c].seen_cnt[seen_msk | np_msk] += cnt;
                            }
                        }
                    }
                }
            }
        }
        return res;
    }

public:
    static int uniquePathsIII(const vector<vector<int>> &grid) {
        const int h = grid.size();
        const int w = grid[0].size();
        P s{0, 0}, e{0, 0};
        int seen_nodes = 0;
        int plen = 0;
        for (int r = 0; r < h; r++) {
            for (int c = 0; c < w; c++) {
                switch (grid[r][c]) {
                    case 1:
                        s = P{r, c};
                        seen_nodes |= node_msk(w, P{r, c});
                        plen++;
                        break;
                    case 2:
                        e = P{r, c};
                        plen++;
                        break;
                    case -1:
                        seen_nodes |= node_msk(w, P{r, c});
                        break;
                    default:
                        plen++;
                }
            }
        }
        vector<vector<M>> bfs(h, vector<M>(w));
        bfs[s.r][s.c].seen_cnt[seen_nodes] = 1;
        for (int l = 1; l < plen; l++)
            bfs = one_bfs_step(bfs);
        return bfs[e.r][e.c].seen_cnt[(1 << h * w) - 1];
    }
};

int main(int argc, char **argv) {
    cout << Solution::uniquePathsIII({{1, 0, 0, 0},
                                      {0, 0, 0, 0},
                                      {0, 0, 2, -1}}) << endl;
    cout << Solution::uniquePathsIII({{1, 0, 0, 0},
                                      {0, 0, 0, 0},
                                      {0, 0, 0, 2}}) << endl;
    return 0;
}
