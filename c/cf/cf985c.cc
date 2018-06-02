#include <iostream>
#include <algorithm>
/* CodeForces CF985C problem */
using namespace std;

int main(int argc, char **argv) {
	int n, k, l;
	cin >> n >> k >> l;
	int m = n*k;
	int aa[m+1];
	aa[m] = INT_MAX;
	for (int i=0; i<m; i++)
		cin >> aa[i];
	sort(aa, aa+m);
	// upper bound search of aa[0]+l
	int f = 0, t = m+1;
	while (f<t) {
		int d = f+(t-f)/2;
		if (aa[d] <= aa[0]+l)
			f = d+1;
		else
			t = d;
	}
	int p = f-1;
	if (p+1>=n) {
		int ans = aa[0];
		n--;
		for (int i=p; i>0 && n--; i--)
			ans += aa[i];
		cout << ans << endl;
	} else {
		cout << 0 << endl;
	}
	return 0;
}
