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
