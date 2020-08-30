#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
/* CodeForces CF...B problem */
using namespace std;

enum { A=0, B=1 };

int main(int argc, char **argv) {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		int sz = 2*n;
		vector<int> vv(sz);
		int pos = 0;
		vector<vector<int>> idx(n+1, vector<int> {-1, -1});
		for (auto &v:vv) {
			cin >> v;
			if (idx[v][0] == -1)
				idx[v][0] = pos;
			else
				idx[v][1] = pos;
			pos++;
		}
		vector<int> ab(sz, -1);
		for (int i=0; i<sz; i++) {
			if (ab[i] == -1) {
				ab[i] = A;
				ab[idx[vv[i]][1]] = B;
			}
		}
		for (int i=0; i<sz; i++)
			if (ab[i] == A)
				cout << vv[i] << ' ';
		cout << '\n';
	}
	return 0;
}
