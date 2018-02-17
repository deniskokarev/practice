/* ACMP 1370 */
#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int64_t mm[n][n];
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			cin >> mm[i][j];
	for (int k=0; k<n; k++)
		for (int i=0; i<n; i++)
			for (int j=0; j<n; j++)
				mm[i][j] = min(mm[i][j], mm[i][k]+mm[k][j]);
	int64_t mm2[n][n];
	memcpy(mm2, mm, sizeof(mm));
	for (int k=0; k<n; k++)
		for (int i=0; i<n; i++)
			for (int j=0; j<n; j++)
				mm2[i][j] = min(mm2[i][j], mm2[i][k]+mm[k][j]);
	int64_t ans = INT_MAX;
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			if (i != j) {
				if (mm2[i][j] >= mm[i][j]) {
					ans = min(ans, mm2[i][j]);
				} else {
					cout << -1 << endl;
					return 0;
				}
			}
		}
	}
	cout << ans << endl;
	return 0;
}
