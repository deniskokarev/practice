#include <iostream>
#include <vector>
#include <numeric>
/* ACMP 378 */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<int> aa(n);
	int sm = 0;
	for (auto &a:aa) {
		cin >> a;
		sm += a;
	}
	sm++;
	vector<vector<int>> dyn(2, vector<int>(2*sm));
	int lvl = 0;
	dyn[0][0] = 1;
	for (int i=0; i<n; i++, lvl^=1) {
		copy(dyn[lvl].begin(), dyn[lvl].begin()+sm, dyn[lvl^1].begin());
		for (int j=0; j<sm; j++)
			dyn[lvl^1][j+aa[i]] |= dyn[lvl][j];
	}
	int ans = accumulate(dyn[lvl].begin(), dyn[lvl].begin()+sm, 0);
	cout << ans << endl;
	return 0;
}
