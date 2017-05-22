#include <iostream>
/* CodeForces CF804B problem */
using namespace std;

const int64_t rem = 1000000007LL;

int main(int argc, char **argv) {
	string s;
	cin >> s;
	int i = 0;
	int l = s.length();
	int64_t res = 0;
	while (i<l && s[i++]=='b');
	int an = 0;
	int64_t pt = 2;
	while (i<l) {
		while (i<l && s[i]=='a') {
			an++;
			i++;
			pt *= 2;
			pt %= rem;
		}
		int bn = 0;
		while (i<l && s[i]=='b') {
			bn++;
			i++;
		}
		int64_t v = bn*(pt-1);
		res += v;
		res %= rem;
	}
	cout << res << endl;
	return 0;
}
