#include <iostream>
/* CodeForces CF884A problem */
using namespace std;

int main(int argc, char **argv) {
	int n, t;
	cin >> n >> t;
	int i;
	for (i=0; i<n && t>0; i++) {
		int d;
		cin >> d;
		t -= 86400;
		t += d;
	}
	cout << i << endl;
	return 0;
}
