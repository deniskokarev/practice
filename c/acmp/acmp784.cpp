/* ACMP 784 */
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int64_t a, b;
	cin >> a >> b;
	int la = 0; // from a to root
	for (int64_t i=a; i>0; i/=2,la++);
	int lb = 0; // from b to root
	for (int64_t i=b; i>0; i/=2,lb++);
	int64_t hi, lo;
	int diff;
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
