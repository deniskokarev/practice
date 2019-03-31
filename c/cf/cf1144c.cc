#include <iostream>
#include <vector>
#include <algorithm>
/* CodeForces CF1144C problem */
using namespace std;

constexpr int MX = 2e5+1;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<int> aa(n);
	vector<int> cnt(MX);
	for (auto &a:aa) {
		cin >> a;
		cnt[a]++;
	}
	vector<vector<int>> res(2, vector<int>());
	bool ans = true;
	for (int a=0; a<MX; a++) {
		if (cnt[a] < 1) {
		} else if (cnt[a] < 2) {
			res[0].push_back(a);
		} else if (cnt[a] < 3) {
			res[0].push_back(a);
			res[1].push_back(a);
		} else {
			ans = false;
		}
	}
	if (ans) {
		cout << "YES" << endl;
		sort(res[0].begin(), res[0].end());
		cout << res[0].size() << endl;
		for (auto r:res[0])
			cout << r << ' ';
		cout << endl;
		sort(res[1].begin(), res[1].end(), std::greater<int>());
		cout << res[1].size() << endl;
		for (auto r:res[1])
			cout << r << ' ';
		cout << endl;
	} else {
		cout << "NO" << endl;
	}
	return 0;
}
