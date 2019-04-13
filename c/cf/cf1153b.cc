#include <iostream>
#include <vector>
/* CodeForces CF1153B problem */
using namespace std;

int main(int argc, char **argv) {
	int n, m, h;
	cin >> n >> m >> h;
	vector<int> xx(m);
	for (int x=0; x<m; x++)
		cin >> xx[x];
	vector<int> yy(n);
	for (int y=0; y<n; y++)
		cin >> yy[y];
	for (int y=0; y<n; y++) {
		for (int x=0; x<m; x++) {
			int p;
			cin >> p;
			cout << min(p*xx[x], p*yy[y]) << ' ';
		}
		cout << '\n';
	}
	return 0;
}
