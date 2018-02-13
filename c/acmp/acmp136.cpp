/* ACMP 136 */
#include <iostream>

using namespace std;

constexpr int LARGE = 101*101;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int mm[n][n];
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			cin >> mm[i][j];
			if (mm[i][j] < 0)
				mm[i][j] = LARGE;
		}
	}
	// floyd
	for (int k=0; k<n; k++)
		for (int i=0; i<n; i++)
			for (int j=0; j<n; j++)
				mm[i][j] = min(mm[i][j], mm[i][k]+mm[k][j]);
	int ans = -1;
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			if (mm[i][j] < LARGE)
				ans = max(ans, mm[i][j]);
	cout << ans << endl;
	return 0;
}
