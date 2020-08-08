class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {
        constexpr int MX_SZ = 1000;
        int sz = arr.size();
        int b = 0;
        for (int i=1; i<=MX_SZ+MX_SZ; i++) {
            if (b >= sz || arr[b] > i) {
                k--;
                if (!k)
                    return i;
            } else {
                b++;
            }
        }
        return -1;
    }
};
