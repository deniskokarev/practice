/* ACMP 150 */
#include <iostream>
#include <vector>

using namespace std;

int seen_cnt(const vector<vector<int>> &mm, vector<int> &seen, int r) {
	if (seen[r])
		return 0;
	seen[r] = true;
	int cnt = 1;
	for (int i=0; i<mm.size(); i++)
		if (mm[r][i])
			cnt += seen_cnt(mm, seen, i);
	return cnt;
};

int main(int argc, char **argv) {
	int n, r;
	cin >> n >> r;
	vector<int> seen(n, false);
	vector<vector<int>> mm(n, vector<int>(n));
	for (auto &mr:mm)
		for (auto &m:mr)
			cin >> m;
	cout << seen_cnt(mm, seen, r-1)-1 << endl;
	return 0;
}
