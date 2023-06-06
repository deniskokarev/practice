// https://leetcode.com/problems/can-make-arithmetic-progression-from-sequence/

// O(1) space solution
class Solution {
    static constexpr unsigned X = 7;

    __attribute__((no_sanitize("integer"))) static inline unsigned pow_x(int p) {
        int r = 1;
        int x = X;
        while (p) {
            if (p&1) {
                r *= x;
            }
            x *= x;
            p /= 2;
        }
        return r;
    }

    static inline bool all_same(const vector<int> &arr, int a) {
        return end(arr) == find_if(begin(arr), end(arr), [a](int b) { return a != b; });
    }

    __attribute__((no_sanitize("integer"))) static inline unsigned expected_hash(int n) {
        int h = 0;
        int px = 1;
        while (n--) {
            h += px;
            px *= X;
        }
        return h;
    }

public:
    static bool canMakeArithmeticProgression(const vector<int> &arr) {
        int sz = arr.size();
        int mn = *min_element(begin(arr), end(arr));
        int mx = *max_element(begin(arr), end(arr));
        int st = (mx - mn) / (sz - 1);
        if (st == 0)
            return all_same(arr, mn);
        unsigned h = 0;
        for (int a: arr) {
            int i = (a - mn) / st;
            if (mn + i * st != a)
                return false;
            h += pow_x(i);
        }
        return h == expected_hash(sz);
    }
};

// trivial solution
class Solution {
public:
    bool canMakeArithmeticProgression(vector<int>& arr) {
        int sz = arr.size();
        if (sz <= 1)
            return true;
        sort(arr.begin(), arr.end());
        int d = arr[1]-arr[0];
        bool ans = true;
        for (int i=1; i<sz; i++)
            ans &= ((arr[i]-arr[i-1]) == d);
        return ans;
    }
};
