/* ACMP 510 */
#include <iostream>
#include <algorithm>

using namespace std;

template<typename T, size_t N> constexpr size_t dim(T (&)[N]) {
	return N;
}

// connectivity matrix
// to get from 2^3 profiles [i][x] -> [i+1][j1],[i+1][j2],...
int mv[8][4] = {
	/* 0 */ {3, 1, 4, 7},
	/* 1 */ {2, 0, 6},
	/* 2 */ {1, 5},
	/* 3 */ {1, 4},
	/* 4 */ {2, 0, 3},
	/* 5 */ {1, 2},
	/* 6 */ {1, 1},
	/* 7 */ {1, 0},
};

int main(int argc, char **argv) {
	int n;
	cin >> n;
	uint64_t pf[2][8] = {{0}}; // 2 layers of 2^3 profiles will suffice
	pf[0][0] = 1;
	for (int i=0; i<n; i++) {
		int cur = i&1;
		int nxt = (i+1)&1;
		fill(pf[nxt], pf[nxt]+dim(pf[nxt]), 0);
		for (int j=0; j<dim(pf[nxt]); j++)
			for (int k=1; k<=mv[j][0]; k++)
				pf[nxt][mv[j][k]] += pf[cur][j];
	}
	cout << pf[n&1][0] << endl;
	return 0;
}
