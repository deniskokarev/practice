#include <iostream>

/* CodeForces CF807B problem */
using namespace std;

bool pp[501][501];

int main(int argc, char **argv) {
	for (int s=0; s<501; s++) {
		int i = s % 475;
		for (int j=0; j<25; j++) {
			i = (i * 96 + 42) % 475;
			pp[s][26 + i] = true;
		}
	}
	int p, x, y;
	cin >> p >> x >> y;
	if (x%50 >= y%50) {
		x /= 50;
		y /= 50;
	} else {
		x /= 50;
		y = (y+49)/50;
	}
	int i = 0;
	while (i>=-x && !pp[x+i][p])
		i--;
	if (x+i < y || !pp[x+i][p]) {
		i = 0;
		while (!(x+i >= y && pp[x+i][p]))
			i++;
		cout << (i+1)/2;
	} else {
		//cerr << i << endl;
		cout << 0;
	}
	cout << endl;
	return 0;
}
