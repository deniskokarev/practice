#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
/* CodeForces CF1216B problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<pair<int,int>> aa(n);
	int i = 1;
	for (auto &a:aa) {
		cin >> a.first;
		a.second = i++;
	}
	sort(aa.begin(), aa.end());
	int64_t ans = 0;
	i = 0;
	for (int j=n-1; j>=0; j--)
		ans += (i++)*aa[j].first+1;
	cout << ans << endl;
	for (int j=n-1; j>=0; j--)
		cout << aa[j].second << ' ';
	cout << endl;
	return 0;
}
