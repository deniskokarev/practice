#include <iostream>
#include <vector>
/* CodeForces CF1015D problem */
using namespace std;

int main(int argc, char **argv) {
	int64_t n, k, s;
	cin >> n >> k >> s;
	vector<int> ans;
	int p = (s+k-1)/k;
	if (p>=n) {
		cout << "NO" << endl;
	} else {
		cout << "YES" << endl;
		int d=1, o=0;
		for (int i=0; i<k-1; i++) {
			o += d*p;
			cout << o+1 << ' ';
			d *= -1;
		}
		int r = s-(k-1)*p;
		o += d*r;
		cout << o+1 << endl;
	}
	return 0;
}
