#include <iostream>
/* CodeForces CF1061A problem */
using namespace std;

int main(int argc, char **argv) {
	int n, s;
	cin >> n >> s;
	int ans = (s+n-1)/n;
	cout << ans << endl;
	return 0;
}
