/* ACMP 1201 */
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int mm[n][n];
	int cnt = 0;
	for (auto &mr:mm) {
		for (auto &m:mr) {
			cin >> m;
			cnt += m;
		}
	}
	cout << n << ' ' << cnt << endl;
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			if (mm[i][j])
				cout << i+1 << ' ' << j+1 << endl;
	return 0;
}
