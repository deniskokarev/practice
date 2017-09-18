/* ACMP 544 */
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	uint64_t cc[4] = {1, 0, 0, 0};
	for (int i=0; i<n; i++) {
		cc[(i+1)&3] += cc[i&3]; // &3 == mod 4
		cc[(i+2)&3] += cc[i&3];
		cc[(i+3)&3] += cc[i&3];
		cc[i&3] = 0;
	}
	cout << cc[n&3] << endl;
	return 0;
}
