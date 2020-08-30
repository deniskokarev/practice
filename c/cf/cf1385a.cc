#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
/* CodeForces CF...A problem */
using namespace std;

int main(int argc, char **argv) {
	int t;
	cin >> t;
	while (t--) {
		int xx[3];
		cin >> xx[0] >> xx[1] >> xx[2];
		sort(xx, xx+3);
		if (xx[1] == xx[2])
			cout << "YES\n" << 1 << " " << xx[0] << " " << xx[1] << "\n";
		else
			cout << "NO\n";
	}
	return 0;
}
