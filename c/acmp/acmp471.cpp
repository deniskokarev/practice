/* ACMP 471 */
#include <iostream>
#include <numeric>

using namespace std;

// cell->(n, nxt1, nxt2)
int nn[10][4] = {
	{2, 4, 6},
	{2, 6, 8},
	{2, 7, 9},
	{2, 4, 8},
	{3, 0, 3, 9},
	{0, -1, -1},
	{3, 0, 1, 7},
	{2, 2, 6},
	{2, 1, 3},
	{2, 2, 4}
};

int main(int argc, char **argv) {
	int n;
	cin >> n;
	uint64_t cc[2][10] = {
		{0, 1, 1, 1, 1, 1, 1, 1, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};
	for (int i=1; i<n; i++)
		for (int j=0; j<10; j++)
			for (int k=1; k<=nn[j][0]; k++)
				cc[i&1][j] += cc[(i+1)&1][nn[j][k]];
	int r = (n+1)&1;
	uint64_t s = accumulate(cc[r], cc[r]+10, 0);
	cout << s << endl;
	return 0;
}
