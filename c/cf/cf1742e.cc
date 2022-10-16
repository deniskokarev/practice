#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
/* CodeForces CF1742E problem */
using namespace std;

int main(int argc, char **argv) {
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        vector<int64_t> aa(n);
        for (auto &a:aa)
            cin >> a;
        vector<int64_t> mxa(n);
        mxa[0] = aa[0];
        for (int i=1; i<n; i++) {
            mxa[i] = max(mxa[i - 1], aa[i]);
            aa[i] += aa[i-1];
        }
        while (q--) {
            int64_t k;
            cin >> k;
            int fnd = upper_bound(mxa.begin(), mxa.end(), k) - mxa.begin();
            if (fnd > 0)
                cout << aa[fnd-1] << ' ';
            else
                cout << 0 << ' ';
        }
        cout << '\n';
    }
	return 0;
}
