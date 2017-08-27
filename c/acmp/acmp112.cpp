#include <iostream>
#include <algorithm>

/* ACMP 112 */
using namespace std;

constexpr int mxp2 = 3; // ceil(log2(10000)) == 14
constexpr int mxn = 1<<mxp2;

int main(int argc, char **argv) {
	int n, k;
	cin >> n >> k;
	int ans = 0;
	for (int ki=0; ki<k; ki++) {
		uint64_t ss[mxp2+1][mxn];
		for (int j=0; j<n; j++)
			cin >> ss[0][j];
		for (int j=n; j<mxn; j++)
			ss[0][j] = ULLONG_MAX;
		for (int i=0; i<mxn; i++)
			cerr << ss[0][i] << ' ';
		cerr << endl;
		for (int l=0, p2=1; l<mxp2; l++,p2*=2) {
			for (int x=0; x < mxn; x+=2*p2)
				merge(&ss[l][x], &ss[l][x+p2],
					  &ss[l][x+p2], &ss[l][x+2*p2],
					  &ss[l+1][x]);
			for (int i=0; i<mxn; i++)
				cerr << ss[l+1][i] << ' ';
			cerr << endl;
		}
		for (int i=1; i<n; i++) {
			int s = ss[0][i];
			for (int d=1,p=i,l=0; d<mxn && p>0; d*=2,l++) {
				if (p%2 == 1) {
					int x = i/d*d-d;
					auto it = lower_bound(&ss[l][x], &ss[l][x+d], s);
					if (it != &ss[l][x+d])
						ans += &ss[l][x+d]-it;
				}
				p /= 2;
			}
		}
	}
	cout << ans << endl;
	return 0;
}
