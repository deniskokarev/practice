#include <iostream>
/* ACMP 526 */
using namespace std;

int main(int argc, char **argv) {
	string a;
	unsigned n;
	cin >> a >> n;
	int b;
	//cerr << a << " = " << n << endl;
	for (b=2;b<37;b++) {
		int m = 0;
		for (int r=1,p=a.size()-1; p>=0; p--,r*=b) {
			int d = (a[p]>='0' && a[p]<='9')?a[p]-'0':a[p]-'A'+10;
			if (d >= b)
				goto nxt;
			m += r*d;
			if (m > 10e7)
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
