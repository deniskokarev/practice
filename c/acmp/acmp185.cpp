/* ACMP 185 */
#include <iostream>
#include <vector>

using namespace std;

int walk_dag(const vector<vector<int>> &mm, vector<int> &seen, int r) {
	if (seen[r])
		return 0;
	seen[r] = 1;
	int cnt = 1;
	for (int i=0; i<mm.size(); i++)
		if (mm[r][i])
			cnt += walk_dag(mm, seen, i);
	return cnt;
};

int main(int argc, char **argv) {
	int n, k;
	cin >> n >> k;
	vector<vector<int>> mm(n, vector<int>(n));
	vector<int> seen(n, 0);
	while (true) {
		int i, j;
		cin >> i;
		if (i == 0)
			break;
		cin >> j;
		i--, j--;
		mm[i][j] = 1;
	}
	cout << ((walk_dag(mm, seen, k-1) == n)?"Yes":"No") << endl;
	return 0;
}
