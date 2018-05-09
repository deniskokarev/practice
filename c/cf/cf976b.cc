#include <iostream>
/* CodeForces CF976B problem */
using namespace std;

int main(int argc, char **argv) {
	int64_t n, m, k;
	cin >> n >> m >> k;
	int x, y;
	if (k>=n) {
		k -= n;
		m--;
		y = n;
		y -= k/m;
		if (k%(2*m) >= m)
			x = m+1-(k%m);
		else
			x = k%m+2;
	} else {
		x = 1;
		y = k+1;
	}
	cout << y << ' ' << x << endl;
	return 0;
}
