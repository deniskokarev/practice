/* ACMP 317 */
#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char **argv) {
	int w;
	int xyz[3]; // wonna make the outer loops the smallest
	cin >> xyz[0] >> xyz[1] >> xyz[2] >> w;
	sort(xyz, xyz+3);
	int z = xyz[0];
	int y = xyz[1];
	int x = xyz[2];
	uint64_t s = 0;
	for (int xs=0,xi=w/x; xi>=0; xi--, xs+=x)
		for (int ys=0,yi=(w-xs)/y; yi>=0; yi--, ys+=y)
			if ((w-(xs+ys)) % z == 0)
				s++;
	cout << s << endl;
	return 0;
}
