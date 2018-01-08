/* ACMP 1358 */
#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

int main(int argc, char **argv) {
	int n, m;
	cin >> n >> m;
	int mm[n][n];
	for (auto &mr:mm)
		fill(mr, mr+n, 0);
	while (m-- > 0) {
		int i, j;
		cin >> i >> j;
		i--, j--;
		mm[i][j] = mm[j][i] = 1;
	}
	bool ans = true;
	for (auto &mr:mm)
		ans &= (accumulate(mr, mr+n, 0) == (n-1));
	cout << (ans?"YES":"NO") << endl;
	return 0;
}
