#include <iostream>
/* CodeForces CF799A problem */
using namespace std;

int main(int argc, char **argv) {
	int n, t, k, d;
	cin >> n >> t >> k >> d;
	int bt = (n+k-1)/k*t;
	if (d < bt-t)
		cout << "YES";
	else
		cout << "NO";
	cout << endl;
	return 0;
}
