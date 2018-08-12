#include <iostream>
#include <vector>
/* CodeForces CF1015D problem */
using namespace std;

int main(int argc, char **argv) {
	int64_t n, k, s;
	cin >> n >> k >> s;
	vector<int> ans;
	int q = s/k;
	int r = s%k;
	if (s<k||q+(r>0)>=n) {
		cout << "NO" << endl;
	} else {
		cout << "YES" << endl;
		int d=1, o=0;
		for (int i=0; i<r; i++) {
			o += d*(q+1);
			cout << o+1 << ' ';
			d *= -1;
		}
		for (int i=r; i<k; i++) {
			o += d*q;
			cout << o+1 << ' ';
			d *= -1;
		}
		cout << endl;
	}
	return 0;
}
