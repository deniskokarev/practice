#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
/* CodeForces CF1742D problem */
using namespace std;

/**
 * GCD(a, b) - greatest common divisor
 */
uint64_t gcd(uint64_t a, uint64_t b) {
    while (b > 0) {
        uint64_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

constexpr int MXA = 1000;

int main(int argc, char **argv) {
    vector<vector<bool>> coprime(MXA + 1, vector<bool>(MXA + 1));
    for (int i = 1; i <= MXA; i++)
        for (int j = i; j <= MXA; j++)
            coprime[i][j] = (gcd(i, j) == 1);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> mxidx(MXA + 1);
        for (int i = 1; i <= n; i++) {
            int a;
            cin >> a;
            mxidx[a] = i;
        }
        int mx = -1;
        for (int i = 1; i <= MXA; i++)
            for (int j = i; j <= MXA; j++)
                if (mxidx[i] > 0 && mxidx[j] > 0 && coprime[i][j])
                    mx = max(mx, mxidx[i] + mxidx[j]);
        cout << mx << endl;
    }
    return 0;
}
