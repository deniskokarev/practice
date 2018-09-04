#include <iostream>
#include <map>
/* CodeForces CF988C problem */
using namespace std;

int main(int argc, char **argv) {
	int k;
	cin >> k;
	map<int64_t, pair<int,int>> s2qp;
	for (int i=0; i<k; i++) {
		int n;
		cin >> n;
		int aa[n];
		int64_t s = 0;
		for (auto &a:aa) {
			cin >> a;
			s += a;
		}
		for (int p=0; p<n; p++) {
			if (s2qp.find(s-aa[p]) != s2qp.end() && s2qp[s-aa[p]].first != i) {
				cout << "YES" << endl;
				cout << s2qp[s-aa[p]].first+1 << ' ' << s2qp[s-aa[p]].second+1 << endl;
				cout << i+1 << ' ' << p+1 << endl;
				return 0;
			}
			s2qp[s-aa[p]] = make_pair(i, p);
		}
	}
	cout << "NO" << endl;
	return 0;
}
