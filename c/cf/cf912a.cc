#include <iostream>
/* CodeForces CF912A problem */
using namespace std;

int main(int argc, char **argv) {
	uint64_t iy, il;
	cin >> iy >> il;
	uint64_t y, g, l;
	cin >> y >> g >> l;
	uint64_t ay, al;
	ay = al = 0;
	if (y*2 > iy) {
		ay += y*2-iy;
		iy = 0;
	} else {
		iy -= y*2;
	}
	if (l*3 > il) {
		al += l*3-il;
		il = 0;
	} else {
		il -= l*3;
	}
	if (g > iy) {
		ay += g-iy;
		iy = 0;
	} else {
		iy -= g;
	}
	if (g > il) {
		al += g-il;
		il = 0;
	} else {
		il -= g;
	}
	cout << ay + al << endl;
	return 0;
}
