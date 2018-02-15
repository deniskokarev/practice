#include <iostream>
#include <cmath>
/* CodeForces CF913A problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	int64_t m;
	cin >> n >> m;
	if (n<33) {
		int64_t mod = 1ULL<<n;
		cout << m % mod << endl;
	} else {
		cout << m << endl;
	}
	return 0;
}
