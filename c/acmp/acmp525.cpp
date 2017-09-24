/* ACMP 525 */
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int l2n = int(ceil(log2(n)))+1;
	vector<vector<uint64_t>> cc(l2n, vector<uint64_t>(n+1));
	for (int i=0; i<=n; i++)
		cc[0][i] = 1;
	int l2, p2;
	for (l2=1,p2=2; l2<l2n; l2++,p2*=2) {
		for (int i=0; i<p2; i++)
			cc[l2][i] = cc[l2-1][i];
		for (int i=p2; i<=n; i++)
			cc[l2][i] = cc[l2][i-p2]+cc[l2-1][i];
	}
	cout << cc[l2-1][n] << endl;
	return 0;
}
