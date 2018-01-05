/* ACMP 1359 */
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	int n, m;
	cin >> n >> m;
	int mm[n][n];
	for (auto &mr:mm)
		fill(mr, mr+n, 0);
	int pos = 0;
	int neg = 0;
	while (m-- > 0) {
		int i, j;
		cin >> i >> j;
		i--, j--;
		if (i != j && mm[i][j] == 0 && mm[j][i] == 0)
			pos++;
		else
			neg++;
		mm[i][j] = mm[j][i] = 1;
	}
	cout << (neg==0 && pos==n*(n-1)/2 ? "YES":"NO") << endl;
	return 0;
}
