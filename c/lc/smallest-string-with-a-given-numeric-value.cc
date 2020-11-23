class Solution {
public:
    string getSmallestString(int n, int k) {
        string ans(n, 'a');
        k -= n;
        int pos = n-1;
        while (k>25) {
            ans[pos--] = 'z';
            k -= 25;
        }
        ans[pos] += k;
        return ans;
    }
};
