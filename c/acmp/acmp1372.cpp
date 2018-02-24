/* ACMP 1372 */
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int mm[n][n];
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			cin >> mm[i][j];
	for (int k=0; k<n; k++)
		for (int i=0; i<n; i++)
			for (int j=0; j<n; j++)
				mm[i][j] = (mm[i][j] || (mm[i][k] && mm[k][j]));
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++)
			cout << mm[i][j] << ' ';
		cout << endl;
	}
	return 0;
}
