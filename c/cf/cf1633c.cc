#include <iostream>
/* CodeForces CF1633C problem */
using namespace std;

inline bool can_win(long long hc, long long dc, long long hm, long long dm) {
    long long mc = (hm + dc - 1) / dc;
    long long mm = (hc + dm - 1) / dm;
    return mc <= mm;
}

int main(int argc, char **argv) {
    int t;
    cin >> t;
    while (t--) {
        long long hc, dc;
        long long hm, dm;
        long long k, w, a;
        cin >> hc >> dc;
        cin >> hm >> dm;
        cin >> k >> w >> a;
        bool ans = false;
        for (long long kw = 0, ka = k; kw <= k; kw++, ka--)
            ans |= can_win(hc + ka * a, dc + kw * w, hm, dm);
        cout << (ans ? "YES" : "NO") << '\n';
    }
    return 0;
}
