#include <iostream>
/* CodeForces CF1139A problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	string s;
	cin >> s;
	int64_t ans = 0;
	for (int i=0; i<n; i++)
		if ((int(s[i]-'0') & 1) == 0)
			ans += (i+1);
	cout << ans << endl;
	return 0;
}
