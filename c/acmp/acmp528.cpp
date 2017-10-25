/* ACMP 528 */
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	int n, k;
	cin >> n >> k;
	uint64_t s = 0;
	for (int i=1; i<=k; i++) {
		s += i*n;
		s -= (i-1)*2+1;
	}
	s++;
	cout << s << endl;
	return 0;
}
