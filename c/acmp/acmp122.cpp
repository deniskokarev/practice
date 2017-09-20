/* ACMP 122 */
#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int aa[n+1];
	aa[0] = INT_MAX;
	for (int i=1; i<=n; i++)
		cin >> aa[i];
	int cc[n+1];
	fill(cc, cc+n+1, 0);
	cc[0] = 0;
	for (int i=1; i<=n; i++) {
		int j;
		for (j=i-1; j>0 && aa[i] <= aa[j]; j--);
		cc[i] = cc[j]+1;
	}
	int mx = 0;
	for (auto c:cc)
		mx = max(mx, c);
	cout << mx << endl;
	return 0;
}
