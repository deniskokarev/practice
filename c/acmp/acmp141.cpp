/* ACMP 141 */
#include <iostream>
#include <vector>

using namespace std;

int walk(const vector<vector<int>> &mm, vector<int> &seen, int r, int p) {
	if (seen[r])
		return -13;
	seen[r] = 1;
	int cnt = 1;
	for (int i:mm[r])
		if (i != p)
			cnt += walk(mm, seen, i, r);
	return cnt;
}

int main(int argc, char **argv) {
	int n;
	cin >> n;
	bool ok = false;
	vector<vector<int>> mm(n);
	for (auto &mr:mm) {
		for (int i=0; i<n; i++) {
			int v;
			cin >> v;
			if (v)
				mr.push_back(i);
		}
		if (mr.size() == 1)
			ok = true;
	}
	for (int i=0; i<n; i++) {
		if (mm[i].size() == 1) {
			vector<int> seen(n, 0);
			int cn = walk(mm, seen, i, -1);
			ok &= (cn == n);
		}
	}
	cout << (ok?"YES":"NO") << endl;
	return 0;
}
