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
