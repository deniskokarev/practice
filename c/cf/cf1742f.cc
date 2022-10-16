#include <iostream>
#include <algorithm>
/* CodeForces CF1742F problem */
using namespace std;

enum { S = 0, T = 1 };

int main(int argc, char **argv) {
    int t;
    cin >> t;
    while (t--) {
        int q;
        cin >> q;
        int64_t stat[2][26]{{0}};
        int mn[2]{0, 0};
        int mx[2]{0, 0};
        while (q--) {
            int st, k;
            cin >> st >> k;
            st--;
            string x;
            cin >> x;
            string nl;
            getline(cin, nl);
            int mn_c = *min_element(x.begin(), x.end()) - 'a';
            int mx_c = *max_element(x.begin(), x.end()) - 'a';
            mn[st] = min(mn[st], mn_c);
            mx[st] = max(mx[st], mx_c);
            for (auto c: x)
                stat[st][c - 'a'] += k;
            bool ans = (mx[T] > 0 || (mx[T] == 0 && mx[S] == 0 && stat[S][0] < stat[T][0]));
            cout << (ans ? "YES" : "NO") << '\n';
        }
    }
    return 0;
}
