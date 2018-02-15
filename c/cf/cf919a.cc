#include <iostream>
#include <iomanip>
/* CodeForces CF919A problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	double m;
	cin >> n >> m;
	double mn = 1e9;
	while (n--) {
		double a, b;
		cin >> a >> b;
		if (a*m/b < mn)
			mn = a*m/b;
	}
	cout << setprecision(9) << mn << endl;
	return 0;
}
