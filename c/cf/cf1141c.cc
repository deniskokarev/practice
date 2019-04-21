#include <iostream>
#include <algorithm>
#include <set>
/* CodeForces CF1141C problem */
using namespace std;

int main(int argc, char **argv) {
	int64_t n;
	cin >> n;
	int qq[n-1];
	for (auto &q:qq)
		cin >> q;
	int pp[n];
	pp[0] = 2e5+1;
	for (int i=0; i<n-1; i++)
		pp[i+1] = pp[i]+qq[i];
	int mn = *min_element(pp, pp+n);
	mn--;
	int64_t sm = 0;
	set<int> all;
	for (int i=0; i<n; i++) {
		pp[i] -= mn;
		sm += pp[i];
		all.insert(pp[i]);
	}
	if (all.size() == n && sm == n*(n+1)/2)
		for (auto p:pp)
			cout << p << ' ';
	else
		cout << -1;
	cout << endl;
	return 0;
}
