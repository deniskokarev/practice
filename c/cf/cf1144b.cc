#include <iostream>
#include <vector>
#include <algorithm>
/* CodeForces CF1144B problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<vector<int>> aa(2, vector<int>());
	int64_t sm = 0;
	for (int i=0; i<n; i++) {
		int a;
		cin >> a;
		aa[a%2].push_back(a);
		sm += a;
	}
	sort(aa[0].begin(), aa[0].end());
	sort(aa[1].begin(), aa[1].end());
	int64_t res = sm;
	int i, j;
	i = aa[0].size()-1;
	j = aa[1].size()-1;
	while (i>=0 && j>=0) {
		res -= aa[0][i--];
		res -= aa[1][j--];
	}
	if (i>=0)
		res -= aa[0][i--];
	if (j>=0)
		res -= aa[1][j--];
	cout << res << endl;
	return 0;
}
