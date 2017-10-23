/* ACMP 156 */
#include <iostream>

using namespace std;

/**
 * factorial n!
 */
uint64_t fact(int n) {
	uint64_t res = 1;
	while (n>1)
		res *= n--;
	return res;
}

int main(int argc, char **argv) {
	int n, k;
	cin >> n >> k;
	uint64_t fk = fact(k);
	uint64_t ans = 1;
	if (k<=n)
		for (uint64_t c=n; k>0; k--, c--)
			ans *= c*c;
	else
		ans = 0;
	cout << ans/fk << endl;
	return 0;
}
