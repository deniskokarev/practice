/* ACMP 954 */
#include <iostream>

using namespace std;

constexpr unsigned mod = 1e6;

enum {
	T = 0,
	B = 1
};

int main(int argc, char **argv) {
	int k;
	cin >> k;
	struct TB {
		unsigned n[2][3]; // 0 - top, 1 - bottom of 1,2,3 glasses
	} nn[k+11]; 
	fill(nn, nn+k+11, TB {{{0, 0, 0}, {0, 0, 0}}});
	nn[10].n[T][0] = nn[10].n[B][0] = 1;
	for (int i=10; i<k; i++) {
		for (int j=0; j<3; j++) {
			nn[i].n[T][j] %= mod;
			nn[i].n[B][j] %= mod;
		}
		nn[i+10].n[T][0] = nn[i].n[B][0] + nn[i].n[B][1] + nn[i].n[B][2];
		nn[i+1].n[T][1] += nn[i].n[T][0];
		nn[i+1].n[T][2] += nn[i].n[T][1];
		nn[i+10].n[B][0] = nn[i].n[T][0] + nn[i].n[T][1] + nn[i].n[T][2];
		nn[i+1].n[B][1] += nn[i].n[B][0];
		nn[i+1].n[B][2] += nn[i].n[B][1];
	}
	unsigned s = 0;
	for (int j=0; j<3; j++) {
		s += nn[k].n[T][j];
		s += nn[k].n[B][j];
	}
	cout << s % mod << endl;
	return 0;
}
