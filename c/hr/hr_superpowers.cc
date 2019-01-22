#include <iostream>
/* Hackerrank https://www.hackerrank.com/challenges/superpowers */
using namespace std;

int b2pn(int b, int n, int m) {
	if (n) {
		int64_t sqb = b2pn(b2pn(b, n/2, m), n/2, m);
		if (n&1)
			return sqb*sqb % m;
		else
			return sqb;
	} else {
		return b % m;
	}
}

int main(int argc, char **argv) {
	int a, b;
	cin >> a >> b;
	cout << b2pn(2, a, b) << endl;
	return 0;
}
