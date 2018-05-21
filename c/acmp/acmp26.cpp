#include <iostream>
/* ACMP 26 */
using namespace std;

int main(int argc, char **argv) {
	int64_t x1, y1, r1;
	int64_t x2, y2, r2;
	cin >> x1 >> y1 >> r1;
	cin >> x2 >> y2 >> r2;
	int64_t dsq = (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
	int64_t rsq = (r1+r2)*(r1+r2);
	cout << ((rsq>=dsq)?"YES":"NO") << endl;
	return 0;
}
