#include <iostream>
/* ACMP 63 */
using namespace std;

int main(int argc, char **argv) {
	int s, p;
	cin >> s >> p;
	int x, y;
	for (x=0; x<1001; x++)
		for (y=0; y<1001; y++)
			if (x+y==s && x*y==p)
				goto end;
 end:
	cout << x << ' ' << y << endl;
	return 0;
}
