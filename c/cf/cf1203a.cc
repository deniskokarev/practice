#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
/* CodeForces CF1203A problem */
using namespace std;

bool find_seq(const vector<int> &aa, int n) {
	auto o = find(aa.begin(), aa.end(), 1);
	int cnt = 1;
	while (o != aa.end() && *o == cnt) {
		o = next(o);
		cnt++;
	}
	return cnt == n+1;
}

int main(int argc, char **argv) {
	int q;
	cin >> q;
	while (q--) {
		int n;
		cin >> n;
		vector<int> aa(2*n);
		for (int i=0; i<n; i++) {
			cin >> aa[i];
			aa[i+n] = aa[i];
		}
		bool a1 = find_seq(aa, n);
		reverse(aa.begin(), aa.end());
		bool a2 = find_seq(aa, n);
		if (a1 || a2)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
	return 0;
}
