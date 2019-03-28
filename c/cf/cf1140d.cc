#include <iostream>
/* CodeForces CF1140D problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int64_t sm = 0;
	for (int i=3; i<=n; i++)
		sm += i*(i-1);
	cout << sm << endl;
	return 0;
}
