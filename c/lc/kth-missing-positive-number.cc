// https://leetcode.com/problems/kth-missing-positive-number/

class Solution {
public:
    static int findKthPositive(const vector<int> &arr, int k) {
        int sz = arr.size();
        int f = 0, t = sz;
        while (f < t) {
            int m = f + (t - f) / 2;
            int miss = arr[m] - m - 1;
            if (miss < k) {
                f = m + 1;
            } else {
                t = m;
            }
        }
        return k + f;
    }
};

class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {
        if (k > arr[0] - 1)
            k -= arr[0] - 1;
        else
            return k;
        int sz = arr.size();
        for (int i=1; i<sz; i++) {
            if (k > arr[i] - arr[i-1] - 1)
                k -= arr[i] - arr[i-1] - 1;
            else
                return arr[i-1] + k;
        }
        return arr[sz-1] + k;
    }
};
