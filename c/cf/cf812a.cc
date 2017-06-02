#include <iostream>
/* CodeForces CF812A problem */
using namespace std;

enum {
	L, S, R, P
};

int main(int argc, char **argv) {
	int tl[4][4];
	for (int i=0; i<4; i++) {
		for (int j=0; j<4; j++) {
			cin >> tl[i][j];
		}
	}
	bool ans = false;
	for (int i=0; i<4; i++) {
		int s = 0;
		for (int j=0; j<3; j++)
			s += tl[i][j];
		if (tl[i][P] && s>0)
			ans = true;
	}
	for (int i=0; i<4; i++) {
		int s = 0;
		for (int j=1; j<4; j++)
			s += tl[(i+j)%4][j-1];
		if (tl[i][P] && s>0)
			ans = true;
	}
	cout << (ans?"YES":"NO") << endl;
	return 0;
}
