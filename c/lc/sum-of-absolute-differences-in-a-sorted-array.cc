class Solution {
    void fw_inc(vector<int> &fw, int pos, int d) {
        int sz = fw.size();
        while (pos < sz) {
            fw[pos] += d;
            pos |= pos+1;
        }
    }
    int fw_sum(vector<int> &fw, int pos) {
        int sm = 0;
        while (pos >= 0) {
            sm += fw[pos];
            pos = (pos & (pos+1))-1;
        }
        return sm;
    }
public:
    vector<int> getSumAbsoluteDifferences(vector<int>& nums) {
        constexpr int MXV = 1e4;
        int sz = nums.size();
        vector<int> fw_cnt(MXV+1);
        vector<int> fw_sm(MXV+1);
        int sm = 0;
        for (int n:nums) {
            fw_inc(fw_cnt, n, +1);
            fw_inc(fw_sm, n, n);
            sm += n;
        }
        vector<int> res(sz);
        for (int i=0; i<sz; i++) {
            int n = nums[i];
            int sm_le = fw_sum(fw_sm, n);
            int cnt_le = fw_sum(fw_cnt, n);
            int sm_gt = sm - sm_le;
            int cnt_gt = sz - cnt_le;
            res[i] = (n*cnt_le - sm_le) + (sm_gt - n*cnt_gt);
        }
        return res;
    }
};
