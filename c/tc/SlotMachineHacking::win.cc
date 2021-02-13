#include <bits/stdc++.h>

using namespace std;

struct  SlotMachineHacking {
    static int win(const vector <string> &reels, const vector <int> &steps) {
        constexpr int MX = 1e5+1;
        int rsz = reels.size();
        int pos[10]{0};
        for (int ans=0; ans<MX; ans++) {
            bool jp = true;
            for (int i=0; i<rsz; i++) {
                pos[i] = (pos[i] + steps[i]) % reels[i].size();
                jp &= (reels[i][pos[i]] == 'c');
            }
            if (jp)
                return ans;
        }
        return -1;
    }
};
