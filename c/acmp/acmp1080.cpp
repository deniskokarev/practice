/* ACMP 1080 */
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int aa[n+1];
	for (int i=1; i<=n; i++)
		cin >> aa[i];
	int m;
	cin >> m;
	while (m-- > 0) {
		string s;
		cin >> s;
		if (s == "get") {
			int i;
			cin >> i;
			cout << aa[i] << endl;
		} else if (s == "update") {
			int l, r, x;
			cin >> l >> r >> x;
			for (int i=l; i<=r; i++)
				aa[i] = x;
		} else if (s == "add") {
			int l, r, x;
			cin >> l >> r >> x;
			for (int i=l; i<=r; i++)
				aa[i] += x;
		} else if (s == "rsq") {
			int l, r;
			cin >> l >> r;
			int s = 0;
			for (int i=l; i<=r; i++)
				s += aa[i];
			cout << s << endl;
		} else if (s == "rmq") {
			int l, r;
			cin >> l >> r;
			int mn = INT_MAX;
			for (int i=l; i<=r; i++)
				mn = min(mn, aa[i]);
			cout << mn << endl;
		}
	}
	return 0;
}
