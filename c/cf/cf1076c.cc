#include <iostream>
#include <iomanip>
#include <cmath>
/* CodeForces CF1076C problem */
using namespace std;

long double get_a(long double d) {
	return (d+sqrtl(d*(d-4.0)))/2.0;
}

int main(int argc, char **argv) {
	int t;
	cin >> t;
	cout << setprecision(13) << fixed;
	while (t--) {
		int d;
		cin >> d;
		if (d*(d-4) < 0) {
			cout << "N\n";
		} else if (d == 0) {
			cout << "Y 0 0\n";
		} else {
			long double a = get_a(d);
			long double b = d-a;
			cout << "Y " << a << " " << b << "\n";
		}
	}
	return 0;
}
