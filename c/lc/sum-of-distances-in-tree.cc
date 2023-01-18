// https://leetcode.com/problems/sum-of-distances-in-tree/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
    struct E {
        int t, sm, cnt;
    };

    using G = vector<vector<E>>;

    // return the sum of dist and number of nodes from p to n
    static E dfs(int n, int p, G &gg) {
        E res{n, 1, 1};
        for (auto &e: gg[n]) {
            if (e.t != p) {
                if (e.sm == -1)
                    e = dfs(e.t, n, gg);
                res.sm += e.sm;
                res.cnt += e.cnt;
            }
        }
        res.sm += res.cnt - 1;
        return res;
    }

public:
    static vector<int> sumOfDistancesInTree(int sz, const vector<vector<int>> &edges) {
        G gg(sz); // we'll update edges as we go
        for (auto &e: edges) {
            gg[e[0]].push_back(E{e[1], -1, -1});
            gg[e[1]].push_back(E{e[0], -1, -1});
        }
        vector<int> ans(sz);
        for (int n = 0; n < sz; n++) {
            E e = dfs(n, -1, gg);
            ans[n] = e.sm - e.cnt; // undo one level
        }
        return ans;
    }
};

int main(int argc, char **argv) {
    auto a1 = Solution::sumOfDistancesInTree(6, {{0, 1},
                                                 {0, 2},
                                                 {2, 3},
                                                 {2, 4},
                                                 {2, 5}});
    for (auto a: a1)
        cerr << a << ' ';
    cerr << endl;
    auto a2 = Solution::sumOfDistancesInTree(1, {});
    for (auto a: a2)
        cerr << a << ' ';
    cerr << endl;
    auto a3 = Solution::sumOfDistancesInTree(2, {{1, 0}});
    for (auto a: a3)
        cerr << a << ' ';
    cerr << endl;
    return 0;
}

