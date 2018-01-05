/* ACMP 784 */
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int a, b;
	cin >> a >> b;
	int la = 0; // from a to root
	for (int i=a; i>0; i/=2,la++);
	int lb = 0; // from b to root
	for (int i=b; i>0; i/=2,lb++);
	int hi, lo, diff;
	if (la>lb) {
		lo = a;
		hi = b;
		diff = la-lb;
	} else {
		lo = b;
		hi = a;
		diff = lb-la;
	}
	while (diff-- > 0)
		lo /= 2;
	while (hi != lo) {
		hi /= 2;
		lo /= 2;
	}
	cout << hi << endl;
	return 0;
}
