/* ACMP 1370 */
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int ans = INT_MAX;
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			int v;
			cin >> v;
			if (v < 0) {
				ans = -1;
				goto done;
			} else if (i!=j) {
				ans = min(ans, v);
			}
		}
	}
 done:
	cout << ans << endl;
	return 0;
}
