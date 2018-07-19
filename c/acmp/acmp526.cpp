#include <iostream>
/* ACMP 526 */
using namespace std;

int main(int argc, char **argv) {
	string a;
	uint64_t n;
	cin >> a >> n;
	unsigned b;
	//cerr << a << " = " << n << endl;
	for (b=2;b<37;b++) {
		uint64_t m = 0;
		uint64_t r = 1;
		for (int p=a.size()-1; p>=0; p--) {
			unsigned d = (a[p]>='A')?a[p]-'A'+10:a[p]-'0';
			if (d >= b)
				goto nxt;
			m += r*d;
			if (m > INT_MAX)
				goto nxt;
			r *= b;
			if (r > INT_MAX)
				goto nxt;
		}
		if (m == n)
			break;
	nxt:
		continue;
	}
	if (b < 37)
		cout << b << endl;
	else
		cout << 0 << endl;
	return 0;
}
