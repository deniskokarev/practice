#include <iostream>
#include <vector>
/* CodeForces CF1025D problem */
using namespace std;

/**
 * GCD(a, b) - greatest common divisor
 */
uint64_t gcd(uint64_t a, uint64_t b) {
	while (b > 0) {
		uint64_t temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}

bool can_bst(const vector<unsigned> &aa, const vector<vector<bool>> &mm, int f, int t, int r) {
	if (t-f == 0) {
		return true;
	} else {
		for (int i=f; i<t; i++)
			if (mm[r][i] && can_bst(aa, mm, f, i, i) && can_bst(aa, mm, i+1, t, i))
				return true;
	}
	return false;
}

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<unsigned> aa(n);
	for (auto &a:aa)
		cin >> a;
	vector<vector<bool>> mm(n+1, vector<bool>(n+1));
	for (int i=0; i<n; i++)
		for (int j=i+1; j<n; j++)
			mm[i][j] = mm[j][i] = (gcd(aa[i], aa[j])>1);
	for (int i=0; i<n; i++)
		mm[i][n] = mm[n][i] = true;
	bool ans = can_bst(aa, mm, 0, n, n);
	cout << (ans?"Yes":"No") << endl;
	return 0;
}
