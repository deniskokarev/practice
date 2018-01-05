/* ACMP 1203 */
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int mm[n][n];
	for (auto &mr:mm)
		fill(mr, mr+n, 0);
	for (int i=0; i<n; i++) {
		int l;
		cin >> l;
		while (l-- > 0) {
			int t;
			cin >> t;
			t--;
			mm[i][t] = 1;
		}
	}
	cout << n << endl;
	for (auto &mr:mm) {
		copy(mr, mr+n, ostream_iterator<int>(cout, " "));
		cout << endl;
	}
	return 0;
}
