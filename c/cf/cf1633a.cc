#include <iostream>
/* CodeForces CF1633A problem */
using namespace std;

int main(int argc, char **argv) {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int d1 = n % 10;
        int d = n - d1;
        int m = n % 7;
        if (d1 >= m)
            d1 -= m;
        else
            d1 += 7 - m;
        cout << d + d1 << '\n';
    }
	return 0;
}
