/* ACMP 562 */
#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char **argv) {
	int n, m;
	cin >> n >> m;
	struct {
		int conn, bwd;
	} mm[n][n];
	memset(mm, 0, sizeof(mm));
	while (m--) {
		int i, j;
		cin >> i >> j;
		i--, j--;
		mm[i][j].conn = 1;
		mm[i][j].bwd = 0;
		if (!mm[j][i].conn) {
			mm[j][i].conn = 1;
			mm[j][i].bwd = 1;
		}
	}
	for (int k=0; k<n; k++)
		for (int i=0; i<n; i++)
			for (int j=0; j<n; j++)
				if (mm[i][j].conn || (mm[i][k].conn && mm[k][j].conn))
					mm[i][j] = { 1, min(mm[i][j].bwd, mm[i][k].bwd+mm[k][j].bwd) };
	int k = 0;
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			k = max(k, mm[i][j].bwd);
	cout << k << endl;
	return 0;
}
