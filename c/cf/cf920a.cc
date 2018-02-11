#include <iostream>
/* CodeForces CF920A problem */
using namespace std;

int main(int argc, char **argv) {
	int t;
	cin >> t;
	while (t--) {
		int n, k;
		cin >> n >> k;
		int x;
		cin >> x;
		int mx = x;
		for (int i=1; i<k; i++) {
			int x1;
			cin >> x1;
			mx = max(mx, (x1-x)/2+1);
			x = x1;
		}
		mx = max(mx, n-x+1);
		cout << mx << endl;
	}
	return 0;
}
