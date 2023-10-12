// https://leetcode.com/problems/find-in-mountain-array
class Solution {
    int summit(MountainArray &aa) {
        int f = 0, t = aa.length() - 1;
        while (f < t) {
            int m = f + (t - f) / 2;
            if (aa.get(m) < aa.get(m+1)) {
                f = m + 1;
            } else {
                t = m;
            }
        }
        return f + 1;
    }
    int search_left(MountainArray &aa, int mid, int k) {
        int f = 0, t = mid;
        while (f < t) {
            int m = f + (t-f)/2;
            if (aa.get(m) < k) {
                f = m + 1;
            } else {
                t = m;
            }
        }
        return f;
    }
    int search_right(MountainArray &aa, int mid, int k) {
        int f = mid, t = aa.length() - 1;
        while (f < t) {
            int m = f + (t-f)/2;
            if (aa.get(m) > k) {
                f = m + 1;
            } else {
                t = m;
            }
        }
        return f;
    }
public:
    int findInMountainArray(int k, MountainArray &aa) {
        int mid = summit(aa);
        int l = search_left(aa, mid, k);
        if (aa.get(l) == k) {
            return l;
        }
        int r = search_right(aa, mid, k);
        if (aa.get(r) == k) {
            return r;
        }
        return -1;
    }
};
