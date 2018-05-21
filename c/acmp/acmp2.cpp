#include <iostream>
/* ACMP 2 */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	if (n > 0)
		cout << (n+1)*n/2 << endl;
	else
		cout << 1-(n-1)*n/2 << endl;
	return 0;
}
