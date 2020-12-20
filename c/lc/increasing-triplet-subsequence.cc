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
