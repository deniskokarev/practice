#include <iostream>
/* ACMP 462 */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int dv = n/2+n/3+n/5-n/6-n/10-n/15+n/30; // num of factors of 2,3,5 using incl/excl principle
	cout << (n - dv) << endl;
	return 0;
}
