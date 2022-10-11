// https://leetcode.com/problems/increasing-triplet-subsequence/

class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int seq[3];
        int seq_sz = 0;
        for (int n:nums) {
            int pos = lower_bound(seq, seq + seq_sz, n) - seq;
            if (pos == seq_sz)
                seq[seq_sz++] = n;
            else if (seq[pos] > n)
                seq[pos] = n;
            if (seq_sz > 2)
                return true;
        }
        return false;
    }
};

class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        const int sz = nums.size();
        vector<int> mnl(nums); // min to the left
        vector<int> mxr(nums); // max to the right
        for (int i=1; i<sz; i++)
            mnl[i] = min(mnl[i-1], mnl[i]);
        for (int i=sz-2; i>=0; i--)
            mxr[i] = max(mxr[i], mxr[i+1]);
        for (int i=1; i<sz-1; i++)
            if (mnl[i-1] < nums[i] && nums[i] < mxr[i+1])
                return true;
        return false;
    }
};
