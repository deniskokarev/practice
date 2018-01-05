/* ACMP 1204 */
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int mm[n][n];
	for (auto &mr:mm)
		for (auto &m:mr)
			cin >> m;
	int sym = true;
	for (int i=0; i<n-1; i++)
		for (int j=i+1; j<n; j++)
			sym &= (mm[i][j] == mm[j][i]);
	cout << (!sym?"YES":"NO") << endl;
	return 0;
}
