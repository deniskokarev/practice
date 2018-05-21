#include <iostream>
/* ACMP 26 */
using namespace std;

int main(int argc, char **argv) {
	int x1, y1, r1;
	int x2, y2, r2;
	cin >> x1 >> y1 >> r1;
	cin >> x2 >> y2 >> r2;
	int dsq = (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
	int rsq_hi = (r1+r2)*(r1+r2);
	int rsq_lo = (r1-r2)*(r1-r2);
	if (rsq_hi >= dsq && dsq >= rsq_lo)
		cout << "YES\n";
	else
		cout << "NO\n";
	return 0;
}
