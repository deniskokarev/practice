// https://leetcode.com/problems/sort-an-array
class Solution {
    static inline pair<int, int> pivot(vector<int> &aa, int b, int e) {
        int l = e - b;
        int r = rand() % l;
        swap(aa[b], aa[b+r]);
        int m = b;
        int v = aa[m];
        while (e > m) {
            if (aa[m] < v) {
                swap(aa[b], aa[m]);
                b++;
                m++;
            } else if (aa[m] > v) {
                swap(aa[e - 1], aa[m]);
                e--;
            } else {
                m++;
            }
        }
        return {b, m};
    }

    static void qsort(vector<int> &aa, int b, int e) {
        if (b < e) {
            auto p = pivot(aa, b, e);
            qsort(aa, b, p.first);
            qsort(aa, p.second, e);
        }
    }

public:
    static vector<int> sortArray(vector<int> &nums) {
        qsort(nums, 0, nums.size());
        return nums;
    }
};
