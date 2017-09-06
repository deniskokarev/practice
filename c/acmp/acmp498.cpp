/* ACMP 498 */
#include <iostream>
#include <algorithm>
#include <vector>
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
	int n, k;
	cin >> n >> k;
	vector<int> aa(n);
	for (int i=0; i<n; i++)
		aa[i] = i;
	size_t sz = fact(aa.size());
	int ans = 0;
	for (size_t i=0; i<sz; i++) {
		int ok = 1;
		for (size_t j=0; j<aa.size()-1; j++) {
			if (abs(aa[j]-aa[j+1]) > k) {
				ok = 0;
				break;
			}
		}
		ans += ok;
		next_permutation(aa.begin(), aa.end());
	}
	cout << ans << endl;
	return 0;
}
