#include <iostream>
/* CodeForces CF1005A problem */
using namespace std;

int main(int argc, char **argv) {
	int ans = 0;
	int n;
	cin >> n;
	int aa[n+1];
	aa[0] = -1;
	int cnt = 0;
	for (int i=1; i<=n; i++) {
		cin >> aa[i];
		if (aa[i] <= aa[i-1]) {
			aa[ans++] = cnt;
			cnt = 0;
		}
		cnt++;
	}
	aa[ans++] = cnt;
	cout << ans << endl;
	for (int i=0; i<ans; i++)
		cout << aa[i] << ' ';
	cout << endl;
	return 0;
}
