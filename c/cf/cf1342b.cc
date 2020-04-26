#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
/* CodeForces CF1342B problem */
using namespace std;

int main(int argc, char **argv) {
	int t;
	cin >> t;
	while (t--) {
		string s;
		cin >> s;
		int hh[2]{0};
		for (auto c:s)
			hh[c-'0']++;
		if (hh[0]*hh[1] == 0) {
			cout << s << '\n';
		} else {
			int sz = s.size();
			int c;
			if (s[0] == '0')
				c = 0;
			else
				c = 1;
			string res;
			for (int i=0; i<sz; i++) {
				res += '0'+c;
				c = !c;
				res += '0'+c;
				c = !c;
			}
			cout << res << '\n';
		}
	}
	return 0;
}
