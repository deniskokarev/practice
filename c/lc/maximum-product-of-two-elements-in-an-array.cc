// https://leetcode.com/problems/maximum-product-of-two-elements-in-an-array
class Solution {
public:
    int maxProduct(const vector<int>& nn) {
        int mx[2] {nn[0], nn[1]};
        sort(mx, mx+2);
        for (int i=2; i<nn.size(); i++) {
            if (nn[i] > mx[1]) {
                mx[0] = mx[1];
                mx[1] = nn[i];
            } else if (nn[i] > mx[0]) {
                mx[0] = nn[i];
            }
        }
        return (mx[0]-1) * (mx[1]-1);
    }
};
