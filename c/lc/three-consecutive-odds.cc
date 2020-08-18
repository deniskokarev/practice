class Solution {
public:
    bool threeConsecutiveOdds(vector<int>& arr) {
        int sz = arr.size();
        if (sz > 2) {
            for (int i=2; i<sz; i++)
                if ((arr[i-2] & arr[i-1] & arr[i]) & 1)
                    return true;
        }
        return false;        
    }
};
