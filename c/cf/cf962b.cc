#include <iostream>
/* CodeForces CF692B problem */
using namespace std;

int main(int argc, char **argv) {
	int n, a, b;
	cin >> n >> a >> b;
	string s;
	cin >> s;
	int len = 0;
	int fspace = 0;
	int ans = 0;
	for (int i=0; i<s.length(); i++) {
		if (s[i] == '*') {
			if (a >= len) {
				a -= len;
				ans += len;
			} else if (b >= len) {
				b -= len;
				ans += len;
			} else {
				fspace += len;
			}
			len = 0;
		} else {
			len++;
		}
	}
	if (a >= len) {
		a -= len;
		ans += len;
	} else if (b >= len) {
		b -= len;
		ans += len;
	} else {
		fspace += len;
	}
	if (fspace > 0) {
		if (a>0) {
			fspace -= a+1;
			ans += a;
			ans += min(b, max(fspace,0));
		} else if (b>0) {
			fspace -= b+1;
			ans += b;
			ans += min(a, max(fspace,0));
		}
	}
	cout << ans << endl;
	return 0;
}
