/* ACMP 671 */
#include <iostream>
#include <algorithm>

using namespace std;

uint32_t f(const int *d, int p) {
	uint32_t s = 0;
	if (p > 0) {
		if (d[p] > 7)
			s = 2UL << p;
		if (d[p] == 7)
			s = f(d, p-1) + (1UL << p);
		else if (d[p] > 4)
			s = (1UL << p);
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

uint32_t F(const int *d, int p) {
	uint32_t s = f(d, p);
	while (p > 0) {
		s += 1UL << p;
		p--;
	}
	return s;
}

int main(int argc, char **argv) {
	uint32_t n;
	cin >> n;
	int d[20] = {0};
	int l = 0;
	while (n>0) {
		d[l++] = n%10;
		n /= 10;
	}
	uint64_t s = F(d, l-1);
	cout << s << endl;
	return 0;
}
