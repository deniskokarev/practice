/* ACMP 1155 */
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// let's store stats as dedicated strings and hope the hashing won't be necessary
int main(int argc, char **argv) {
	int k, n, m;
	cin >> k >> n >> m;
	vector<vector<string>> mm(n, vector<string>(m, string(k, '.')));
	for (int pik=0; pik<k; pik++) {
		for (int r=0; r<n; r++) {
			string s;
			cin >> s;
			for (int c=0; c<s.length(); c++)
				mm[r][c][pik] = s[c];
		}
	}
	vector<string> ss;
	for (int r=0; r<n; r++)
		for (int c=0; c<m; c++)
			ss.push_back(mm[r][c]);
	sort(ss.begin(), ss.end());
	int sz = unique(ss.begin(), ss.end()) - ss.begin();
	cout << sz << endl;
	return 0;
}
