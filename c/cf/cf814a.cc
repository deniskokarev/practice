#include <iostream>
#include <algorithm>

/* CodeForces CF814A problem */
using namespace std;

int main(int argc, char **argv) {
	int n, k;
	cin >> n >> k;
	int aa[n];
	for (auto &a:aa)
		cin >> a;
	int bb[k];
	for (auto &b:bb)
		cin >> b;
	int j = 0;
	int cc[n];
	copy(aa, aa+n, cc);
	for (int i=0; i<n; i++)
		if (!cc[i])
			cc[i] = bb[j++];
	sort(cc, cc+n);
	bool rc = true;	// may not break the order
	for (int i=0; i<n; i++) {
		if (aa[i] && aa[i] != cc[i]) {
			rc = false;
			break;
		}
	}
	int l = 0;
	for (int i=0; i<n; i++) {
		if (!aa[i]) {
			l = i;
			break;
		}
	}
	int r = 0;
	for (int i=n-1; i>=0; i--) {
		if (!aa[i]) {
			r = i;
			break;
		}
	}
	if (l<r && cc[l]<cc[r])
		rc = false;
	cout << (rc?"No":"Yes") << endl;
	return 0;
}
