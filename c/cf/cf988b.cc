#include <iostream>
#include <vector>
/* CodeForces CF988B problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<string> ll(n);
	for (auto &l:ll)
		cin >> l;
	bool ans = true;
	for (int i=0; i<n; i++) {
		for (int j=i+1; j<n; j++) {
			if (ll[i].find(ll[j]) != string::npos) {
				swap(ll[i], ll[j]);
			} else if (ll[j].find(ll[i]) != string::npos) {
				// ok
			} else {
				ans = false;
				goto end;
			}
		}
	}
 end:
	if (ans) {
		cout << "YES" << endl;
		for (auto l:ll)
			cout << l << endl;
	} else {
		cout << "NO" << endl;
	}
	return 0;
}
