/* ACMP 1014 */
#include <iostream>

using namespace std;

constexpr uint64_t mod = 1e9+9;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	// number of non-uniq hamiltonian paths in the graph
	// ans = ((n-1)!/2)*(n-1)
	uint64_t ans = (n-1);
	for (uint64_t i=3; i<n; i++) {
		ans *= i;
		ans %= mod;
	}
	cout << ans << endl;
	return 0;
}
