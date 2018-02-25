/* ACMP 1370 */
#include <iostream>
#include <cstring>

using namespace std;

constexpr int DMIN = INT_MIN/2;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int mm[n][n];
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			cin >> mm[i][j];
	// floyd
	for (int k=0; k<n; k++)
		for (int i=0; i<n; i++)
			for (int j=0; j<n; j++)
				mm[i][j] = min(mm[i][j], max(DMIN, mm[i][k]+mm[k][j]));
	bool nl = false;
	int ans;
	// check main diag for neg loops
	for (int i=0; i<n; i++)
		nl |= (mm[i][i]<0);
	if (nl) {
		ans = -1;
	} else {
		ans = INT_MAX;
		for (int i=0; i<n; i++)
			for (int j=0; j<n; j++)
				if (i != j)
					ans = min(ans, mm[i][j]);
	}
	cout << ans << endl;
	return 0;
}
