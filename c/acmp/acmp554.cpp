/* ACMP 554 */
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	uint64_t s = 1;
	for (int i=1; i<=n; i++)
		s = s+i;
	cout << s << endl;
	return 0;
}
