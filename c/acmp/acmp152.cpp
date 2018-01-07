/* ACMP 152 */
#include <iostream>
#include <vector>

using namespace std;

bool has_loops(const vector<vector<int>> &mm, int node, vector<int> &seen) {
	if (seen[node] != 0)
		return true;
	seen[node] = 1;
	for (auto i:mm[node])
		if (has_loops(mm, i, seen))
			return true;
	seen[node] = 0;
	return false;
}

int main(int argc, char **argv) {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> mm(n);
	while (m--) {
		int i, j;
		cin >> i >> j;
		i--, j--;
		mm[i].push_back(j);
	}
	vector<int> seen(n, 0);
	bool ans = true;
	for (int i=0; i<n; i++) {
		if (has_loops(mm, i, seen)) {
			ans = false;
			break;
		}
	}
	cout << (ans?"Yes":"No") << endl;
	return 0;
}
