class Solution {
public:
    bool canFormArray(vector<int>& arr, vector<vector<int>>& pieces) {
        for (auto &pp:pieces) {
            int len = pp.size();
            auto fnd = search(arr.begin(), arr.end(), pp.begin(), pp.end());
            if (fnd != arr.end())
                for (int i=0; i<len; i++)
                    *(fnd++) = -2342548;
            else
                return false;
        }
        return true;
    }
};
