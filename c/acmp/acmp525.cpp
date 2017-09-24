/* ACMP 525 */
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<uint64_t> cc(n+1, 1);
	for (int p2=2; p2<=n; p2*=2)
		for (int i=p2; i<=n; i++)
			cc[i] += cc[i-p2];
	cout << cc[n] << endl;
	return 0;
}
