/* ACMP 113 */
#include <vector>
#include <iostream>

using namespace std;

struct P {
	int x, y;
};

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<vector<P>> mm(n, vector<P>(n, {0, 0}));
	for (int i=0; i<n; i++) {
		string s;
		cin >> s;
		for (int j=0; j<n; j++)
			if (s[j] == '1')
				mm[i][j].x = mm[i][j].y = 1;
	}
	for (int i=0; i<n; i++)
		for (int j=1; j<n; j++)
			if (mm[i][j].x)
				mm[i][j].x += mm[i][j-1].x;
	for (int i=1; i<n; i++)
		for (int j=0; j<n; j++)
			if (mm[i][j].y)
				mm[i][j].y += mm[i-1][j].y;
	int a = 0;
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			a = max(a, min(mm[i][j].x, mm[i][j].y));
	cout << a*a << endl;
	return 0;
}
