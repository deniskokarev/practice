/* ACMP 893 */
#include <iostream>
using namespace std;

int main(int argc, char **argv) {
	uint64_t n;
	cin >> n;
	if (n>2) {
		cout << n*(n-1)*(n-2);
	} else if (n>1) {
		cout << n*(n-1);
	} else if (n>0) {
		cout << n;
	} else {
		cout << 0;
	}
	cout << endl;
	return 0;
}
