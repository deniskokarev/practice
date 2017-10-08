/* ACMP 100 */
#include <iostream>
#include <cassert>

using namespace std;

/*
 * f[n,s] - number of digit permutations of
 * n - length of the half
 * s - sum of digits in that half
 * f[n,s] = f[n-1,s]+f[n-1,s-1]+..f[n-1,0] // number <= 10, last 10 go down 9,8,7.. elements
 * f[1,0] = 1
 * f[1,1] = 1
 * ...
 * f[1,9] = 1
 */
int main(int argc, char **argv) {
	int nd;
	cin >> nd;
	assert((nd&1) == 0);
	int n = nd/2;
	assert(n < 51);
	uint64_t f[2][n*9+1];
	fill(f[0], f[0]+10, 1);
	int h = 10;
	for (int i=1; i<n; i++) {
		int cur = i&1;
		int prev = (i+1)&1;
		int j = 0;
		uint64_t s = 0;
		while (j<10) {
			s += f[prev][j];
			f[cur][j] = s;
			j++;
		}
		while (j<h) {
			s += f[prev][j];
			s -= f[prev][j-10];
			f[cur][j] = s;
			j++;
		}
		h += 9;
		while (j<h) {
			s -= f[prev][j-10];
			f[cur][j] = s;
			j++;
		}
	}
	int cur = (n+1)&1;
	uint64_t ss = 0;
	for (int i=0; i<n*9+1; i++)
		ss += f[cur][i]*f[cur][i];
	cout << ss << endl;
	return 0;
}
