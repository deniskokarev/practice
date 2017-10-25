/* ACMP 317 */
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	int x, y, z, w;
	cin >> x >> y >> z >> w;
	int s = 0;
	int xm = w/x, ym = w/y, zm = w/z;
	for (int xs=0,xi=0; xi<=xm; xi++, xs+=x)
		for (int ys=0,yi=0; yi<=ym; yi++, ys+=y)
			for (int zs=0,zi=0; zi<=zm; zi++, zs+=z)
				if (xs+ys+zs == w)
					s++;
	cout << s << endl;
	return 0;
}
