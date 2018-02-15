#include <iostream>
/* CodeForces CF915A problem */
using namespace std;

int main(int argc, char **argv) {
	int n, k;
	cin >> n >> k;
	int mn = INT_MAX;
	while (n--) {
		int a;
		cin >> a;
		if (k%a == 0)
			mn = min(mn, k/a);
	}
	cout << mn << endl;
	return 0;
}
