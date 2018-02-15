#include <iostream>
#include <cmath>

/* CodeForces CF914A problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int mx = INT_MIN;
	while (n--) {
		int a;
		cin >> a;
		if (a >= 0) {
			double da = a;
			double s = sqrt(da);
			int si = int(s);
			if (si * si != a)
				mx = max(mx, a);
		} else {
			mx = max(mx, a);
		}
	}
	cout << mx << endl;
	return 0;
}
