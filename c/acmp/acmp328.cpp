/* ACMP 328 */
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	uint64_t s = 0;
	for (int i=0; i<=n; i++)
		for (int j=i; j<=n; j++)
			s += i+j;
	cout << s << endl;
	return 0;
}
