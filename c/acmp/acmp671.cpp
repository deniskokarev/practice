/* ACMP 671 */
#include <iostream>
#include <algorithm>

using namespace std;

unsigned f(const int *d, int p) {
	unsigned s = 0;
	if (p > 0) {
		if (d[p] > 7)
			s = 2U << p;
		if (d[p] == 7)
			s = f(d, p-1) + (1U << p);
		else if (d[p] > 4)
			s = (1U << p);
		else if (d[p] == 4)
			s = f(d, p-1);
	} else if (p == 0) {
		if (d[p] >= 7)
			s = 2;
		else if (d[p] >= 4)
			s = 1;
	}
	return s;
}

unsigned F(const int *d, int p) {
	unsigned s = f(d, p);
	while (p > 0) {
		s += 1U << p;
		p--;
	}
	return s;
}

int main(int argc, char **argv) {
	unsigned n;
	cin >> n;
	int d[12] = {0};
	int l = 0;
	while (n>0) {
		d[l++] = n%10;
		n /= 10;
	}
	uint64_t s = F(d, l-1);
	cout << s << endl;
	return 0;
}
