/* ACMP 1368 */
#include <iostream>

using namespace std;

constexpr int64_t LARGE = 50*50*50*10e6;

int main(int argc, char **argv) {
	int n, s, t;
	cin >> n >> s >> t;
	s--, t--;
	int64_t mm[n][n];
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			cin >> mm[i][j];
			if (mm[i][j] < 0)
				mm[i][j] = LARGE;
		}
	}
	// floyd
	for (int k=0; k<n; k++)
		for (int i=0; i<n; i++)
			for (int j=0; j<n; j++)
				mm[i][j] = min(mm[i][j], mm[i][k]+mm[k][j]);
	cout << ((mm[s][t]<LARGE)?mm[s][t]:-1) << endl;
	return 0;
}
