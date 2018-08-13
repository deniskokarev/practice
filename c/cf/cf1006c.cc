#include <iostream>
/* CodeForces CF1006C problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int64_t dd[n+2];
	for (int i=1; i<=n; i++)
		cin >> dd[i];
	int64_t ll[n+2], rr[n+2];
	ll[0] = 0;
	for (int i=1; i<=n; i++)
		ll[i] = ll[i-1]+dd[i];
	rr[n+1] = 0;
	for (int i=n; i>=1; i--)
		rr[i] = rr[i+1]+dd[i];
	int l=0, r=n+1;
	int64_t mx = -1;
	while (l<r) {
		if (ll[l] == rr[r]) {
			mx = max(mx, ll[l]);
			l++, r--;
		} else if (ll[l] < rr[r]) {
			l++;
		} else {
			r--;
		}
	}
	cout << mx << endl;
	return 0;
}
