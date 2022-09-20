// https://leetcode.com/problems/maximum-length-of-repeated-subarray/
// CPU = O(N * log(N)) solution
// Mem = O(N)
#include <vector>
#include <numeric>
#include <iostream>
#include <unordered_set>

using namespace std;

constexpr int P = 127;
constexpr int MOD = 1e9 + 7;

class Solution {
public:
    struct H {
        const vector<int> &v;
        vector<int> h;
        vector<int> p;

        H(const vector<int> &_v) : v(_v), h(v.size() + 1), p(v.size() + 1) {
            p[0] = 1;
            for (int i = 0; i < v.size(); i++) {
                int64_t lh = h[i] + int64_t(v[i]) * p[i];
                h[i + 1] = int(lh % MOD);
                p[i + 1] = int((int64_t(p[i]) * P) % MOD);
            }
        }

        int64_t operator()(int b, int e) const {
            return h[e] + MOD - h[b];
        }
    };

    struct HAB {
        H ha;
        H hb;
        const vector<int> &p;
        int mxsz;

        HAB(const vector<int> &a, const vector<int> &b) : ha(a), hb(b), p(hb.p), mxsz(p.size()) {
        }

        int nh(const H &h, int b, int e) const {
            int m = p[mxsz - e - 1];
            return (h(b, e) * m) % MOD;
        }

        int nha(int b, int e) const {
            return nh(ha, b, e);
        }

        int nhb(int b, int e) const {
            return nh(hb, b, e);
        }
    };

    static bool has_match(int l, const HAB &hab) {
        unordered_set<int> h;
        for (int i = l; i < hab.ha.h.size(); i++)
            h.insert(hab.nha(i - l, i));
        for (int i = l; i < hab.hb.h.size(); i++)
            if (h.find(hab.nhb(i - l, i)) != h.end())
                return true; // let's hope we'll be lucky without precise comparison confirmation
        return false;
    }

    static int findLength(const vector<int> &nums1, const vector<int> &nums2) {
        int sz1 = nums1.size(), sz2 = nums2.size();
        const vector<int> &a = (sz1 > sz2) ? nums2 : nums1;
        const vector<int> &b = (sz1 <= sz2) ? nums2 : nums1;
        HAB hab(a, b);
        int f = 0, t = sz1 + 1;
        while (f < t) {
            int m = (f + t) / 2;
            if (has_match(m, hab))
                f = m + 1;
            else
                t = m;
        }
        return f - 1;
    }
};

int main() {
    Solution::HAB hab({1, 2, 3}, {1, 2, 3, 4, 5});
    for (int i = 0; i < 4; i++)
        cerr << hab.ha.h[i] << ' ';
    cerr << endl;
    for (int i = 0; i < 6; i++)
        cerr << hab.ha.h[i] << ' ';
    cerr << endl;
    cerr << hab.nha(1, 2) << endl;
    cerr << hab.nhb(1, 2) << endl;
    cout << Solution::findLength({1, 2, 3, 2, 1}, {3, 2, 1, 4, 7}) << endl;
    cout << Solution::findLength({0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}) << endl;
    cout << Solution::findLength({1}, {0}) << endl;
    cout << Solution::findLength({70,39,25,40,7},{52,20,67,5,31}) << endl;
}
