class Solution {
public:
    bool validateBinaryTreeNodes(int sz, const vector<int> &lc, const vector<int> &rc) {
        vector<int> in_cnt(sz), out_cnt(sz);
        int e_cnt = 0;
        for (int i=0; i<sz; i++) {
            const int &c = lc[i];
            if (c>=0) {
                in_cnt[c]++;
                out_cnt[i]++;
                e_cnt++;
            }
        }
        for (int i=0; i<sz; i++) {
            const int &c = rc[i];
            if (c>=0) {
                in_cnt[c]++;
                out_cnt[i]++;
                e_cnt++;
            }
        }
        bool all_have_e = true;
        for (int i=0; i<sz; i++)
            all_have_e &= ((in_cnt[i] > 0)||(out_cnt[i] > 0));
        return ((sz==1)||all_have_e) && (e_cnt == sz-1); 
    }
};
