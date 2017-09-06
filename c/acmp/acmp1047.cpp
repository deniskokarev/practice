/* ACMP 1047 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>
#include <cassert>

using namespace std;

/**
 * factorial n!
 */
uint64_t fact(int n) {
	assert(n < 21);	// 64bit overflow with n>=21
	uint64_t res = 1;
	while (n>1)
		res *= n--;
	return res;
}

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<vector<int>> mm(n, vector<int>(n));
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			cin >> mm[i][j];
	vector<int> pp(n);
	for (int i=0; i<n; i++)
		pp[i] = i;
	size_t sz = fact(n);	
	uint64_t mn = ULLONG_MAX;
	for (size_t i=0; i<sz; i++) {
		uint64_t sum = 0;
		for (int j=0; j<n; j++)
			sum += mm[j][pp[j]];
		mn = min(mn, sum);
		next_permutation(pp.begin(), pp.end());
	}
	cout << mn << endl;
	return 0;
}
