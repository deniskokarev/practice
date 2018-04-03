#include <iostream>
/* CodeForces CF884B problem */
using namespace std;

int main(int argc, char **argv) {
	int n, x;
	cin >> n >> x;
	int s = 0;
	for (int i=0; i<n; i++) {
		int a;
		cin >> a;
		s += a;
	}
	bool ans = ((x-s) == (n-1));
	cout << (ans?"YES":"NO") << endl;
	return 0;
}
