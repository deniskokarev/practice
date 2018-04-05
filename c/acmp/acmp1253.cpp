/* ACMP 1253 */
#include <iostream>

using namespace std;

int gcd(int a, int b) {
	if (a == 0)
		return b;
	else if (b == 0)
		return a;
	else if (a > b)
		return gcd(a%b, b);
	else
		return gcd(a, b%a);
}

int main(int argc, char **argv) {
	int a, b;
	cin >> a >> b;
	cout << a/gcd(a,b)*b << endl;
	return 0;
}
