/* ACMP 552 */
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<uint64_t> aa(n+1);
	for (int i=1; i<=n; i++)
		cin >> aa[i];
	vector<vector<uint64_t>> cc(2, vector<uint64_t>(max(n+1, 4), 1));
	for (int s=1; s<4; s++) {
		for (int i=0; i<s; i++)
			cc[s&1][i] = 0;
		for (int i=s; i<=n; i++)
			cc[s&1][i] = cc[s&1][i-1] + cc[(s+1)&1][i-1]*aa[i];
	}
	cout << cc[1][n] << endl;
	return 0;
}
