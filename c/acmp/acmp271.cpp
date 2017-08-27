#include <iostream>
/* ACMP 271 */
using namespace std;

int main(int argc, char **argv) {
	uint64_t n;
	cin >> n;
	uint64_t f1=1, f2=2;
	int i=3;
	while (f2 < n) {
		uint64_t f = f1+f2;
		f1 = f2;
		f2 = f;
		i++;
	}
	if (f2 == n)
		cout << "1\n" << i;
	else
		cout << "0";
	cout << endl;
	return 0;
}

