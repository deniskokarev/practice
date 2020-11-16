class Solution {
public:
    vector<int> decrypt(vector<int>& code, int k) {
        int sz = code.size();
        vector<int> cc(3*sz);
        copy(code.begin(), code.end(), cc.begin());
        copy(code.begin(), code.end(), cc.begin()+sz);
        copy(code.begin(), code.end(), cc.begin()+2*sz);
        vector<int> res(sz);
        int j=sz;
        for (int i=0,j=sz; i<sz; i++,j++) {
            if (k>0)
                res[i] = accumulate(cc.begin()+j+1, cc.begin()+j+k+1, 0);
            else if (k<0)
                res[i] = accumulate(cc.begin()+j+k, cc.begin()+j, 0);
            else
                res[i] = 0;
        }
        return res;
    }
};
