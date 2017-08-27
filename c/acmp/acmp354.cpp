#include <iostream>
using namespace std;
int main() {
	uint64_t n;
	cin >> n;
	int cnt=0;
	for (uint64_t p=2; p*p<=n; p++) {
		while (n%p == 0) {
			cout << ((cnt++==0)?"":"*") << p;
			n /= p;
		}
	}
	if (n>1)
		cout << ((cnt++==0)?"":"*") << n;
	cout << endl;
	return 0;
}

