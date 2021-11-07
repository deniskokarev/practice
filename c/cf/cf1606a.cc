#include <iostream>
/* CodeForces CF1606A problem */
using namespace std;

int main(int argc, char **argv) {
    int t;
    cin >> t;
    string s;
    getline(cin, s); // skip newline
    while (t--) {
        getline(cin, s);
        if (s.front() != s.back()) {
            int ord = s[0] - 'a';
            ord ^= 1;
            s[0] = 'a'+ord;
        }
        cout << s << '\n';
    }
	return 0;
}
