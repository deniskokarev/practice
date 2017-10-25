/* ACMP 317 */
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	int x, y, z, w;
	cin >> x >> y >> z >> w;
	int s = 0;
	for (int xi=0; xi<=w/x; xi++)
		for (int yi=0; yi<=w/y; yi++)
			for (int zi=0; zi<=w/z; zi++)
				if (x*xi+y*yi+z*zi == w)
					s++;
	cout << s << endl;
	return 0;
}
