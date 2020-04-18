class Solution {
public:
    int numFriendRequests(vector<int>& ages) {
        int aa[121]{0};
        for (int a:ages)
            aa[a]++;
        int ans = 0;
        for (int a=0; a<=120; a++) {
            for (int b=0; b<=120; b++) {
                if (a>=b && a<2*b-14 && (a>=100 || b<=100)) {
                    if (a>b)
                        ans += aa[a]*aa[b];
                    else if (a==b)
                        ans += aa[a]*(aa[a]-1);
                }
            }
        }
        return ans;
    }
};
