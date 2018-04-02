/* ACMP 1371 */
#include <iostream>
#include <iomanip>

using namespace std;

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
				mm[i][j] |= mm[i][k] & mm[k][j];
	string ans = "No";
	for (int i=0; i<n; i++)
		if (mm[i][i])
			ans = "Yes";
	cout << ans << endl;
	return 0;
}
