class Solution {
public:
    int sumOddLengthSubarrays(vector<int>& arr) {
        int sz = arr.size();
        vector<int> sm(sz+1);
        for (int i=0; i<sz; i++)
            sm[i+1] = sm[i]+arr[i];
        int res = 0;
        for (int i=1; i<=sz; i++)
            for (int j=i-1; j>=0; j-=2)
                res += sm[i]-sm[j];
        return res;
    }
};
