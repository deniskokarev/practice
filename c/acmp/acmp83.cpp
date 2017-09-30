/* ACMP 83 */
#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

char *sbit(int n, int p2n, char *s) {
	for (int p=0; p<p2n; p++,n>>=1)
		s[p] = (n&1)?'1':'0';
	return s;
}

bool kosher(int len, const char *si, const char *sj) {
	for (int p=0; p<len-1; p++)
		if (si[p] == sj[p] && si[p] == si[p+1] && si[p+1] == sj[p+1])
			return false;
	return true;
}

int main(int argc, char **argv) {
	int in, im;
	cin >> in >> im;
	int n = min(in, im);
	int m = max(in, im);
	int p2n = 1<<n;
	unsigned cc[2][p2n];
	fill(cc[0], cc[0]+p2n, 1);
	char si[p2n];
	char sj[p2n];
	for (int k=1; k<m; k++) {
		fill(cc[k&1], cc[k&1]+p2n, 0);
		for (int i=0; i<p2n; i++) {
			sbit(i, n, si);
			for (int j=0; j<p2n; j++)
				if (kosher(n, si, sbit(j, n, sj)))
					cc[k&1][j] += cc[(k+1)&1][i];
		}
	}
	unsigned ans = accumulate(cc[(m+1)&1], cc[(m+1)&1]+p2n, 0U);
	cout << ans << endl;
	return 0;
}
