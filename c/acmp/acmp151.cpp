/* ACMP 151 */
#include <iostream>
#include <vector>

using namespace std;

bool walk(const vector<vector<int>> &mm, vector<int> &seen, int r, int color) {
	if (seen[r])
		return (seen[r] == color);
	seen[r] = color;
	bool ok = true;
	for (int i:mm[r])
		ok &= walk(mm, seen, i, (color%2)+1);
	return ok;
}

int main(int argc, char **argv) {
	int n, m;
	cin >> n >> m;
	vector<int> color(n, 0);
	vector<vector<int>> mm(n);
	while (m-- > 0) {
		int i, j;
		cin >> i >> j;
		i--, j--;
		mm[i].push_back(j);
		mm[j].push_back(i);
	}
	bool ok = true;
	for (int i=0; i<n; i++)
		if (color[i] == 0)
			ok &= walk(mm, color, i, 1);
	cout << (ok?"YES":"NO") << endl;
	return 0;
}
