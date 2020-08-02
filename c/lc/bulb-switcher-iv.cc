class Solution {
public:
    int minFlips(const string &target) {
        bool flip = false;
        int cnt = 0;
        int sz = target.size();
        for (int i=0; i<sz; i++) {
            bool state = (target[i]=='0') ^ flip;
            if (!state) {
                flip = !flip;
                cnt++;
            }
        }
        return cnt;
    }
};
