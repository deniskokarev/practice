/* ACMP 125 */
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int mm[n][n];
	for (auto &mr:mm)
		for (auto &m:mr)
			cin >> m;
	int cc[n];
	for (auto &c:cc)
		cin >> c;
	int cnt=0;
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			if (mm[i][j] && cc[i] != cc[j])
				cnt++;
	cout << cnt/2 << endl;
	return 0;
}
