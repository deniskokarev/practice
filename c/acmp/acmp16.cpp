/* ACMP 16 */
#include <iostream>

using namespace std;

unsigned cnt(int n, int base) {
	unsigned c = 0;
	if (n > 0 && base > 0 && n >= base) {
		c++;
		while (n>base) {
			n--;
			c += cnt(n, base-1);
		}
		for (int i=1; i<n; i++)
			c += cnt(i, base-i-1);
	}
	return c;
}

int main(int argc, char **argv) {
	int n;
	cin >> n;
	cout << cnt(n, n) << endl;
	return 0;
}
