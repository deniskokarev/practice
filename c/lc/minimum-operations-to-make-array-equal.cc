class Solution {
public:
    int minOperations(int n) {
        int h = n/2;
        return h*(h+(n&1));
    }
};
