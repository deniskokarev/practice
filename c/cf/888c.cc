#include <iostream>
#include <algorithm>
/* CodeForces CF888C problem */
using namespace std;

int main(int argc, char **argv) {
	string s;
	cin >> s;
	int p[256];
	fill(p, p+256, -1);
	int mxl[256];
	fill(mxl, mxl+256, -1);
	for (int i=0; i<s.size(); i++) {
		short c = s[i];
		if (p[c] != -1)
			mxl[c] = max(mxl[c], i-p[c]);
		else
			mxl[c] = i;
		p[c] = i;
	}
	int i = s.size();
	for (short c='a'; c<='z'; c++)
		if (p[c] != -1)
			mxl[c] = max(mxl[c], i-p[c]);
	int ans = INT_MAX;
	for (int c='a'; c<='z'; c++)
		if (p[c] != -1)
			ans = min(ans, mxl[c]);
	cout << ans << endl;
	return 0;
}
