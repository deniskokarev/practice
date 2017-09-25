/* ACMP 480 */

#include <iostream>
#include <vector>

using namespace std;

struct SC {
	uint64_t s[2];
};

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<uint64_t> aa(n);
	for (int i=0; i<n; i++)
		cin >> aa[i];
	int k;
	cin >> k;
	// (p,n,k) -> (sc1,sc2)
	vector<vector<vector<SC>>> sc(2, vector<vector<SC>>(n+1, vector<SC>(k, {{0,0}})));
	for (int i=n-1; i>=0; i--) {
		for (int p=0; p<2; p++) {
			uint64_t s = 0;
			for (int k1=0; k1<k && i+k1<n; k1++) {
				s += aa[i+k1];
				sc[p][i][k1] = sc[!p][i+k1+1][k1];
				sc[p][i][k1].s[p] += s;
			}
			for (int k1=1; k1<k; k1++)
				if (sc[p][i][k1].s[p] < sc[p][i][k1-1].s[p])
					sc[p][i][k1] = sc[p][i][k1-1];
		}
	}
	cout << sc[0][0][k-1].s[0] << endl;
	return 0;
}
