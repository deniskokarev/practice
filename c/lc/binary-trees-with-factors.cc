// https://leetcode.com/problems/binary-trees-with-factors/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

constexpr int MOD = 1e9 + 7;

class Solution {
    struct E {
        long a, b;
    };
public:
    static int numFactoredBinaryTrees(const vector<int> &arr) {
        int sz = arr.size();
        vector<int> aa(arr);
        sort(begin(aa), end(aa));
        vector<vector<E>> ee(sz);
        for (int i = 0; i < sz; i++) {
            for (int j = 0; j < sz; j++) {
                long long prod = ((long long) aa[i]) * aa[j];
                int p = std::lower_bound(aa.begin(), aa.end(), (int) prod) - aa.begin();
                if (prod <= 2e9 && p < sz && aa[p] == prod)
                    ee[p].push_back(E{i, j});
            }
        }
        vector<long long> cnt(sz, {1});
        for (int i = 0; i < sz; i++)
            for (auto e: ee[i])
                cnt[i] += (cnt[e.a] * cnt[e.b]) % MOD;
        return accumulate(begin(cnt), end(cnt), 0L, [](long long a, long long b) { return (a + b) % MOD; });
    }
};

int main(int argc, char **argv) {
    cout << Solution::numFactoredBinaryTrees({2, 4}) << endl;
    cout << Solution::numFactoredBinaryTrees({2, 4, 5, 10}) << endl;
    return 0;
}

