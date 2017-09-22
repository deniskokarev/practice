/* ACMP 122 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<int> ll(n+1, INT_MAX);
	int mx = 2;
	ll[0] = INT_MIN;
	for (int i=0; i<n; i++) {
		int a;
		cin >> a;
		auto f = upper_bound(ll.begin(), ll.begin()+mx, a);
		if (*(f-1) < a) {
			*f = min(*f, a);
			mx = max(mx, int(f-ll.begin())+1);
		}
	}
	cout << mx-1 << endl;
	return 0;
}
