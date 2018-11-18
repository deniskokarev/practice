#include <iostream>
#include <algorithm>
/* CodeForces CF1064A problem */
using namespace std;

int main(int argc, char **argv) {
	int aa[3];
	cin >> aa[0] >> aa[1] >> aa[2];
	sort(aa, aa+3);
	int ans = aa[2]-aa[0]-aa[1]+1;
	if (ans > 0)
		cout << ans << endl;
	else
		cout << 0 << endl;
	return 0;
}
