/* ACMP 24 */
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	int n, m;
	cin >> n >> m;
	uint64_t s = 0;
	if (m>1)
		for (int d=0; (m-1)*d+m <= n; d++)
			s += (n-(m-1)*d-m)+1;
	else if (m == 1)
		s = n;
	else
		s = 1;
	cout << s << endl;
	return 0;
}
