/* ACMP 1202 */
#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char **argv) {
	int n, m;
	cin >> n >> m;
	int mm[n][n+1];
	for (auto &mr:mm)
		mr[0] = 0;
	while (m-- > 0) {
		int u, v;
		cin >> u >> v;
		u--;
		mm[u][1+mm[u][0]++] = v;
	}
	cout << n << endl;
	for (int i=0; i<n; i++) {
		cout << mm[i][0] << ' ';
		sort(mm[i]+1, mm[i]+1+mm[i][0]);
		for (int j=0; j<mm[i][0]; j++)
		    cout << mm[i][1+j] << ' ';
		cout << endl;
	}
	return 0;
}
