#include <iostream>
#include <vector>
/* CodeForces CF803B problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<int64_t> aa(n);
	vector<int> zz;
	zz.push_back(-1e9);
	for (int i=0; i<n; i++) {
		cin >> aa[i];
		if (aa[i] == 0)
			zz.push_back(i);
	}
	zz.push_back(1e9);
	int l = 0, r = 1;
	for (int i=0; i<n; i++) {
		if (aa[i] == 0) {
			cout << 0 << ' ';
			l++;
			r++;
		} else {
			cout << min(i-zz[l], zz[r]-i) << ' ';
		}
	}
	cout << endl;
	return 0;
}
