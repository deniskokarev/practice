class Solution {
    int sum_quot(const vector<int>& nums, int div) {
        int sm=0;
        for (int n:nums)
            sm += (n+div-1)/div;
        return sm;
    }
public:
    int smallestDivisor(const vector<int>& nums, int threshold) {
        int f=1,t=INT_MAX-1;
        while (f<=t) {
            int mid = f+(t-f)/2;
            if (sum_quot(nums, mid) > threshold)
                f = mid+1;
            else
                t = mid-1;
        }
        return t+1;
    }
};
