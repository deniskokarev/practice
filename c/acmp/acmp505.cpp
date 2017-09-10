/* ACMP 505 */
#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main(int argc, char **argv) {
	int l, m, n;
	cin >> l >> m >> n;
	map<vector<int>, int> ttmap;
	for (int i=0; i<m; i++) {
		vector<int> tt(l);
		int id;
		cin >> id;
		for (auto &t:tt)
			cin >> t;
		ttmap[tt] = id;
	}
	int ok=0, bad=0;
	for (int i=0; i<n; i++) {
		vector<int> ss(l);
		for (auto &s:ss)
			cin >> s;
		auto fnd = ttmap.find(ss);
		if (fnd != ttmap.end()) {
			cout << fnd->second;
			ok++;
		} else {
			cout << '-';
			bad++;
		}
		cout << endl;
	}
	cout << "OK=" << ok << " BAD=" << bad << endl;
	return 0;
}
