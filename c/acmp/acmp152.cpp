/* ACMP 152 */
#include <iostream>
#include <vector>

using namespace std;

enum {
	EMPTY = 0,
	VISITING = 1,
	DONE = 2
};

bool has_loops(const vector<vector<int>> &mm, int node, vector<int> &seen) {
	if (seen[node] == VISITING)
		return true;
	else if (seen[node] == DONE)
		return false;
	seen[node] = VISITING;
	for (auto i:mm[node])
		if (has_loops(mm, i, seen))
			return true;
	seen[node] = DONE;
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
	vector<int> seen(n, EMPTY);
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
