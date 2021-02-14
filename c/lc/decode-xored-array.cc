class Solution {
public:
    vector<int> decode(vector<int>& encoded, int first) {
        int sz = encoded.size();
        vector<int> res(sz+1);
        res[0] = first;
        for (int i=0; i<sz; i++)
            res[i+1] = res[i] ^ encoded[i];
        return res;
    }
};
