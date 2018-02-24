/* ACMP 1374 */
#include <iostream>

using namespace std;

constexpr int DINF = INT_MAX/2;

int main(int argc, char **argv) {
	int n, m;
	cin >> n >> m;
	int mm[n][n];
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			mm[i][j] = DINF;
	for (int i=0; i<n; i++)
		mm[i][i] = 0;
	while (m--) {
		int i, j, l;
		cin >> i >> j >> l;
		i--, j--;
		mm[i][j] = l;
		mm[j][i] = l;
	}
	for (int k=0; k<n; k++)
		for (int i=0; i<n; i++)
			for (int j=0; j<n; j++)
				mm[i][j] = min(mm[i][j], mm[i][k]+mm[k][j]);
	int mx[n];
	for (int i=0; i<n; i++)
		mx[i] = 0;
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			mx[i] = max(mx[i], mm[i][j]);
	int mni = 0;
	for (int i=0; i<n; i++)
		if (mx[i] < mx[mni])
			mni = i;
	cout << mni+1 << endl;
	return 0;
}
