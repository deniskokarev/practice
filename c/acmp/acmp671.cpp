/* ACMP 671 */
#include <iostream>
#include <algorithm>

using namespace std;

uint64_t f(const string &d, int p) {
	uint64_t s = 0;
	if (p > 0) {
		if (d[p] > '7')
			s = 2ULL << p;
		else if (d[p] == '7')
			s = f(d, p-1) + (1ULL << p);
		else if (d[p] > '4')
			s = (1ULL << p);
		else if (d[p] == '4')
			s = f(d, p-1);
	} else if (p == 0) {
		if (d[p] >= '7')
			s = 2;
		else if (d[p] >= '4')
			s = 1;
	}
	return s;
}

uint64_t F(const string &d, int p) {
	uint64_t s = f(d, p);
	while (p > 0) {
		s += 1ULL << p;
		p--;
	}
	return s;
}

int main(int argc, char **argv) {
	string sn;
	cin >> sn;
	int l = sn.length();
	reverse(sn.begin(), sn.end());
	uint64_t a = F(sn, l-1);
	cout << a << endl;
	return 0;
}
