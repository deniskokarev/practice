#include <iostream>
/* CodeForces CF1037C problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	string a, b;
	cin >> a >> b;
	int ans = 0;
	for (int i=0; i<n-1; i++) {
		if (a[i] != b[i] && a[i+1] != b[i+1] && a[i] == b[i+1] && a[i+1] == b[i]) {
			swap(a[i], a[i+1]);
			ans++;
		}
	}
	for (int i=0; i<n; i++) {
		if (a[i] != b[i])
			ans++;
	}
	cout << ans << endl;
	return 0;
}
