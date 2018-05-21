#include <iostream>
/* ACMP 43 */
using namespace std;

int main(int argc, char **argv) {
	string s;
	cin >> s;
	int cnt = 0;
	int mx = INT_MIN;
	for (auto c:s) {
		if (c == '0')
			cnt++;
		else
			cnt = 0;
		mx = max(mx, cnt);
	}
	cout << mx << endl;
	return 0;
}
