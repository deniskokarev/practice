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
	vector<vector<P>> mm(n+1, vector<P>(n+1, {0, 0}));
	for (int i=1; i<=n; i++) {
		string s;
		cin >> s;
		for (int j=1; j<=n; j++)
			if (s[j-1] == '1')
				mm[i][j].x = mm[i][j].y = 1;
	}
	int a = 0;
	for (int i=1; i<=n; i++) {
		for (int j=1; j<=n; j++) {
			if (mm[i][j].x) {
				mm[i][j].x = min(mm[i][j-1].x+1, mm[i-1][j-1].x+1);
				mm[i][j].y = min(mm[i-1][j].y+1, mm[i-1][j-1].y+1);
			}
			a = max(a, min(mm[i][j].x, mm[i][j].y));
		}
	}
	cout << a*a << endl;
	return 0;
}
