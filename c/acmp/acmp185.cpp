/* ACMP 185 */
#include <iostream>
#include <vector>

using namespace std;

int walk_tree(const vector<vector<int>> &mm, int r) {
	int cnt = 1;
	for (int i=0; i<mm.size(); i++)
		if (mm[r][i])
			cnt += walk_tree(mm, i);
	return cnt;
};

int main(int argc, char **argv) {
	int n, k;
	cin >> n >> k;
	vector<vector<int>> mm(n, vector<int>(n));
	while (true) {
		int i, j;
		cin >> i;
		if (i == 0)
			break;
		cin >> j;
		i--, j--;
		mm[i][j] = 1;
	}
	cout << ((walk_tree(mm, k-1) == n)?"Yes":"No") << endl;
	return 0;
}
