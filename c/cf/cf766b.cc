#include <iostream>
#include <vector>
#include <algorithm>

/* CodeForces CF766B problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i=0; i<n; i++)
		cin >> a[i];
	sort(a.begin(), a.end());
	bool rc = false;
	for (int i=0; i<n-2; i++) {
		if (a[i]+a[i+1] > a[i+2]) {
			rc = true;
			break;
		}
	}
	cout << (rc?"YES":"NO") << endl;
	return 0;
}
