/* ACMP 116 */
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	int n, m;
	cin >> n >> m;
	unsigned pp[n][m]; // care only about heights at each point
	for (int i=0; i<n; i++) {
		string s;
		cin >> s;
		for (int j=0; j<m; j++)
			if (s[j] == '1')
				pp[i][j] = 1;
			else
				pp[i][j] = 0;
	}
	// all hights
	for (int i=1; i<n; i++)
		for (int j=0; j<m; j++)
			if (pp[i][j] > 0)
				pp[i][j] = pp[i-1][j] + pp[i][j];
	// debug
	cerr << endl;
	for (int i=0; i<n; i++) {
		for (int j=0; j<m; j++)
			cerr << pp[i][j];
		cerr << endl;
	}
	unsigned mxs = 0;
	for (int i=0; i<n; i++) {
		struct {unsigned x, h;} hh[m]; // stack of hights and their x start coord
		int top = 0;
		hh[top] = {0, pp[i][0]};
		for (unsigned j=1; j<m; j++) {
			if (hh[top].h < pp[i][j]) {
				top++;
				hh[top] = {j, pp[i][j]};
			} else if (hh[top].h > pp[i][j]) {
				while (top >= 0 && hh[top].h > pp[i][j]) {
					unsigned s = hh[top].h * (j-hh[top].x);
					mxs = max(mxs, s);
					top--;
				}
				top++;
				hh[top].h = pp[i][j];
			}
		}
		while (top >= 0) {
			unsigned s = hh[top].h * (m-hh[top].x);
			mxs = max(mxs, s);
			top--;
		}
	}
	cout << mxs << endl;
	return 0;
}
