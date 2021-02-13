#include <bits/stdc++.h>

using namespace std;

struct TIEFighterAssembly {
    static int assemble(const string &salvagedParts) {
        int cnt[256]{0};
        for (unsigned char c:salvagedParts)
            cnt[c]++;
        return min({cnt['|']/2, cnt['-']/2, cnt['O']});
    }
};
