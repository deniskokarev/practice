#include <iostream>
/* CodeForces CF810A problem */
using namespace std;

int main(int argc, char **argv) {
	int n, k;
	cin >> n >> k;
	int s = 0;
	for (int i=0; i<n; i++) {
		int a;
		cin >> a;
		s += a;
	}
	int m = n*(2*k-1)-2*s;
	if (m > 0)
		cout << m;
	else
		cout << 0;
	cout << endl;
	return 0;
}
