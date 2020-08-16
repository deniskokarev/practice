#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
/* CodeForces CF...B problem */
using namespace std;

int main(int argc, char **argv) {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		vector<pair<int,int>> gg(n);
		for (auto &g:gg)
			cin >> g.first;
		for (auto &g:gg)
			cin >> g.second;
		int mn_a = INT_MAX, mn_b = INT_MAX;
		for (auto &g:gg) {
			mn_a = min(mn_a, g.first);
			mn_b = min(mn_b, g.second);
		}
		int64_t mv = 0;
		for (auto &g:gg) {
			int sub_a = g.first - mn_a;
			int sub_b = g.second - mn_b;
			mv += max(sub_a, sub_b);
		}
		cout << mv << "\n";
	}
	return 0;
}
