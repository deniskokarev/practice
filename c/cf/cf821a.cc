#include <iostream>
/* CodeForces CF821A problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int aa[n][n];
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			cin >> aa[i][j];
	bool rr[n][n];
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			rr[i][j] = false;
			for (int k=0; k<n; k++) {
				for (int l=0; l<n; l++) {
					if (aa[i][j] == 1) {
						rr[i][j] = true;
					} else if (aa[i][j] == aa[i][k]+aa[l][j]) {
						rr[i][j] = true;
					}
				}
			}
		}
	}
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			if (rr[i][j] == false) {
				cout << "No" << endl;
				return 0;
			}
		}
	}
	cout << "Yes" << endl;
	return 0;
}
