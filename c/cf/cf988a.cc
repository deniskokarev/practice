#include <iostream>
#include <algorithm>
#include <cstring>
/* CodeForces CF988A problem */
using namespace std;

int main(int argc, char **argv) {
	int n, k;
	cin >> n >> k;
	int aa[n];
	int pp[101];
	for (int i=0; i<n; i++) {
		cin >> aa[i];
		pp[aa[i]] = i;
	}
	sort(aa, aa+n);
	int sz = unique(aa, aa+n)-aa;
	if (sz >= k) {
		cout << "YES" << endl;
		for (int i=0; i<k; i++)
			cout << pp[aa[i]]+1 << ' ';
		cout << endl;
	} else {
		cout << "NO" << endl;
	}
	return 0;
}
