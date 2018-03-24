/* ACMP 162 */
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	int n, m;
	cin >> n >> m;
	// using euler cycle trick - adding extra edgest to all odd-power nodes
	// if all nodes were having even power the ideal cycle would be
	int ans = n*(m+1)+m*(n+1); // ideal path
	// but we need to account for odd-power nodes too, for those we have
	// to add extra paths
	ans += (n-1)+(m-1);
	// now if either side is even length we need to add exra 2 for corner cases
	if ((n&1)==0 || (m&1)==0)
		ans += 2;
	cout << ans << endl;
	return 0;
}
