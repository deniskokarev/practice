class Solution {
    enum {EQ, LT, GT};
public:
    int longestMountain(vector<int>& arr) {
        int sz = arr.size();
        int cnt[3]{0};
        int mx = 0;
        int state = EQ;
        for (int i=1; i<sz; i++) {
            if (arr[i-1] < arr[i]) {
                if (state != LT) {
                    state = LT;
                    cnt[LT] = 1;
                }
                cnt[LT]++;
            } else if (arr[i-1] > arr[i]) {
                if (state != GT) {
                    state = GT;
                    cnt[GT] = 1;
                }
                cnt[GT]++;
                if (cnt[LT])
                    mx = max(mx, cnt[LT]+cnt[GT]-1);
            } else {
                cnt[GT] = cnt[LT] = 0;
                state = EQ;
            }
        }
        return mx;
    }
};
