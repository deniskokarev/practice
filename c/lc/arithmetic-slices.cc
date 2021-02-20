class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& aa) {
        int sz = aa.size();
        int sm = 0;
        int l = 0;
        for (int i=2; i<sz; i++) {
            if (aa[i]-aa[i-1] == aa[i-1]-aa[i-2])
                l++;
            else
                l = 0;
            sm += l;
        }
        return sm;
    }
};
