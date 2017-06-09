#include <iostream>
#include <set>
#include <vector>
/* CodeForces CF814B problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int aa[n];
	for (auto &a:aa)
		cin >> a;
	int bb[n];
	for (auto &b:bb)
		cin >> b;
	int d = 0;
	vector<int> aan(n+1, 0);
	for (int i=0; i<n; i++) {
		if (aa[i] != bb[i]) {
			d++;
		} else {
			aan[aa[i]]++;
		}
	}
	set<int> nn;
	for (int i=1; i<=n; i++)
		if (aan[i] == 0)
			nn.insert(i);
	if (d > 1) {
		for (int i=0; i<n; i++)
			if (aa[i] != bb[i] && nn.find(bb[i]) != nn.end()) {
				aa[i] = bb[i];
				break;
			}
	} else {
		for (int i=0; i<n; i++)
			if (aa[i] != bb[i]) {
				aa[i] = *nn.begin();
				break;
			}
	}
 	for (auto &a:aa)
		cout << a << ' ';
	cout << endl;
	return 0;
}
