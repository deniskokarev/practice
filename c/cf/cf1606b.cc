#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
/* CodeForces CF1606B problem */
using namespace std;

int main(int argc, char **argv) {
    int t;
    cin >> t;
    while (t--) {
        long long n, k;
        cin >> n >> k;
        int h = 0;
        long long s = 1;
        n -= s;
        while (s < k) {
            h++;
            n -= s;
            s += s;
        }
        if (n > 0)
            cout << h + (n+k-1)/k << '\n';
        else
            cout << h << '\n';
    }
	return 0;
}
