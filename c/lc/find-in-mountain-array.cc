// https://leetcode.com/problems/find-in-mountain-array
class Solution {
    static int summit(MountainArray &aa) {
        int f = 0, t = aa.length() - 1;
        while (f < t) {
            int m = f + (t - f) / 2;
            if (aa.get(m) < aa.get(m + 1)) {
                f = m + 1;
            } else {
                t = m;
            }
        }
        return f + 1;
    }

    template<class Compare>
    static int search_lb(MountainArray &aa, int f, int t, int k, Compare comp) {
        while (f < t) {
            int m = f + (t - f) / 2;
            if (comp(aa.get(m), k)) {
                f = m + 1;
            } else {
                t = m;
            }
        }
        return f;
    }

public:
    static int findInMountainArray(int k, MountainArray &aa) {
        int mid = summit(aa);
        int l = search_lb(aa, 0, mid, k, less<int>());
        if (aa.get(l) == k) {
            return l;
        }
        int r = search_lb(aa, mid, aa.length() - 1, k, greater<int>());
        if (aa.get(r) == k) {
            return r;
        }
        return -1;
    }
};

