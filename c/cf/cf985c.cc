#include <iostream>
#include <algorithm>
/* CodeForces CF985C problem */
using namespace std;

int main(int argc, char **argv) {
	int n, k;
	int l;
	cin >> n >> k >> l;
	int m = n*k;
	int aa[m+1];
	aa[m] = INT_MAX;
	for (int i=0; i<m; i++)
		cin >> aa[i];
	sort(aa, aa+m);
	int p = upper_bound(aa, aa+m+1, aa[0]+l)-aa;
	if (p>=n) {
		int64_t ans = 0;
		int i = 0;
		while (i<=p-n && n) {
			ans += aa[i];
			for (int j=0; j<k && i<=p-n; j++,i++);
			n--;
		}
		cout << ans << endl;
	} else {
		cout << 0 << endl;
	}
	return 0;
}
