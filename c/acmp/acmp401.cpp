/* ACMP 401 */
#include <iostream>
using namespace std;

uint64_t cnt(int n, int a) {
	uint64_t s = 0;
	if (n>0)
		for (int i=0; i<=a; i++)
			s += cnt(n-1, i);
	else
		s++;
	return s;
}

int main(int argc, char **argv) {
	int n, a, b;
	cin >> n >> a >> b;
	cout << cnt(n, a) * cnt(n, b) << endl;
	return 0;
}
