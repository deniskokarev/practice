#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
/* CodeForces CF1742C problem */
using namespace std;

int main(int argc, char **argv) {
    int t;
    cin >> t;
    string nl;
    getline(cin, nl);
    while (t--) {
        getline(cin, nl);
        char ans = 'B';
        for (int i=0; i<8; i++) {
            string s;
            getline(cin, s);
            bool is_r = true;
            for (auto c:s)
                is_r &= (c == 'R');
            if (is_r)
                ans = 'R';
        }
        cout << ans << endl;
    }
    return 0;
}
