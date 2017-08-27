#include <iostream>
/* ACMP 323 */
using namespace std;

#define dim(X)	(sizeof(X)/sizeof(X[0]))

bool nprimes[1024] = {false};

int main() {
	int i=2;
	while (i<dim(nprimes)/2) {
		for (int j=i+i;j<dim(nprimes);j+=i)
			nprimes[j] = true;
		for (i++; (i<dim(nprimes) && nprimes[i]); i++);
	}
	int n;
	cin >> n;
	for (int i=2;i<=n/2;i++) {
		if (!nprimes[i] && !nprimes[n-i]) {
			cout << i << ' ' << n-i << endl;
			break;
		}
	}
}
