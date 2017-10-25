/* ACMP 317 */
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	int x, y, z, w;
	cin >> x >> y >> z >> w;
	uint64_t s = 0;
	for (int xs=0,xi=w/x; xi>=0; xi--, xs+=x)
		for (int ys=0,yi=(w-xs)/y; yi>=0; yi--, ys+=y)
			if ((w-(xs+ys)) % z == 0)
				s++;
	cout << s << endl;
	return 0;
}
