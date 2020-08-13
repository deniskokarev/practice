class Solution {
public:
    int getLastMoment(int n, vector<int>& left, vector<int>& right) {
        int szl = left.size();
        int szr = right.size();
        if (szl>0 && szr>0) {
            int mxl = *max_element(left.begin(), left.end());
            int mnr = n - *min_element(right.begin(), right.end());
            return max(mxl, mnr);
        } else if (szl>0) {
            return *max_element(left.begin(), left.end());
        } else {
            return n - *min_element(right.begin(), right.end());
        }
    }
};
