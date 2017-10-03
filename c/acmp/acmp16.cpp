/* ACMP 16 */
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<vector<unsigned>> cc(n+1, vector<unsigned>(n+1, 0));
	for (int i=0; i<=n; i++)
		cc[i][i] = 1;
	for (int i=1; i<=n; i++)
		for (int b=1; b<=n; b++)
			for (int k=b+1; k+i<=n; k++)
				cc[k+i][k] += cc[i][b];
	cout << accumulate(&cc[n][1], &cc[n][n+1], 0ULL) << endl;
	return 0;
}
