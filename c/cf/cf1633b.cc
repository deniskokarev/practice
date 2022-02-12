#include <iostream>
#include <algorithm>
/* CodeForces CF1633B problem */
using namespace std;

int main(int argc, char **argv) {
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        int cnt[]{0,0};
        for (char c:s)
            cnt[c-'0']++;
        if (cnt[0] == cnt[1])
            cout << cnt[0] - 1 << '\n';
        else
            cout << min(cnt[0], cnt[1]) << '\n';
    }
	return 0;
}
