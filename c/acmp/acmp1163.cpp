/* ACMP 1163 */
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	int64_t n;
	int64_t a, b;
	cin >> n >> a >> b;
	n = n*100 + n*a;
	n = (n+50)/100;
	n = n*100 - n*b;
	n = (n+50)/100;
	cout << n << endl;
	return 0;
}
