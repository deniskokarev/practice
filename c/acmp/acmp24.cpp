/* ACMP 24 */
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	int n, m;
	cin >> n >> m;
	uint64_t s = 0;
	for (int d=0; d<n; d++) {
		if ((m-1)*d+m > n)
			break;
		s += (n-(m-1)*d-m)+1;
	}
	cout << s << endl;
	return 0;
}
