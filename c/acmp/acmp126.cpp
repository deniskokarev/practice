/* ACMP 126 */
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int mm[n][n];
	for (auto &mr:mm)
		for (auto &m:mr)
			cin >> m;
	int mn = INT_MAX;
	for (int i=0; i<n-2; i++)
		for (int j=i+1; j<n-1; j++)
			for (int k=j+1; k<n; k++)
				mn = min(mn, mm[i][j]+mm[j][k]+mm[k][i]);
	cout << mn << endl;
	return 0;
}
