#include <iostream>
/* CodeForces CF1114A problem */
using namespace std;

int main(int argc, char **argv) {
	int x, y, z;
	cin >> x >> y >> z;
	int a, b, c;
	cin >> a >> b >> c;
	bool ans;
	if (x <= a) {
		a -= x;
		if (z <= c) {
			ans = (a+b) >= y;
		} else {
			z -= c;
			ans = a+b >= y+z;
		}
	} else {
		ans = false;
	}
	cout << (ans?"YES":"NO") << endl;
	return 0;
}
