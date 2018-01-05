/* ACMP 1356 */
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	for (int i=0; i<n; i++) {
		int cnt = 0;
		int l;
		for (int j=0; j<n; j++) {
			cin >> l;
			cnt += l;
		}
		cout << cnt << ' ';
	}
	cout << endl;
	return 0;
}
