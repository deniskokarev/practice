#include <iostream>
#include <algorithm>
/* CodeForces CF977C problem */
using namespace std;

int main(int argc, char **argv) {
	int n, k;
	cin >> n >> k;
	int aa[n];
	for (auto &a:aa)
		cin >> a;
	sort(aa, aa+n);
	int f=0, t=n;
	while (f<t) {
		int m=f+(t-f)/2;
		auto p = upper_bound(aa, aa+n, m);
		int cnt = p-aa;
		//cerr << "m=" << m << " cnt= " << cnt << endl;
		if (cnt > k) {
			t = m;
		} else if (cnt < k) {
			f = m+1;
		} else {
			cout << m+1 << endl;
			goto end;
		}
	}
	cout << -1 << endl;
 end:
	return 0;
}
