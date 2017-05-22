#include <iostream>
#include <vector>
/* CodeForces CF803A problem */
using namespace std;

int main(int argc, char **argv) {
	int n, k;
	cin >> n >> k;
	vector<vector<int>> mm(n, vector<int>(n));
	for (int r=0; r<n && k>0; r++) {
		mm[r][r] = 1;
		k--;
		for (int i=r+1; i<n && k>1; i++) {
			mm[i][r] = 1;
			mm[r][i] = 1;
			k--; k--;
		}
	}
	if (k>0) {
		cout << -1 << endl;
	} else {
		for (int r=0; r<n; r++) {
			for (int c=0; c<n; c++)
				cout << mm[r][c] << ' ';
			cout << endl;
		}
	}
	return 0;
}
