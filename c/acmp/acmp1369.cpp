/* ACMP 1369 */
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int64_t mm[n][n];
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			cin >> mm[i][j];
	// floyd
	for (int k=0; k<n; k++)
		for (int i=0; i<n; i++)
			for (int j=0; j<n; j++)
				mm[i][j] = min(mm[i][j], mm[i][k]+mm[k][j]);
	int64_t ans = -1;
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			ans = max(ans, mm[i][j]);
	cout << ans << endl;
	return 0;
}
