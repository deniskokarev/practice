#include <iostream>
/* CodeForces CF962B problem */
using namespace std;

int main(int argc, char **argv) {
	int n, ab[2];
	string s;
	cin >> n >> ab[0] >> ab[1];
	cin >> s;
	int was = ab[0]+ab[1];
	int last_idx = -1;
	for (int i=0; i<s.length(); i++) {
		if (s[i] == '.') {
			if (last_idx == 0) {
				if (ab[1] > 0) {
					ab[1]--;
					last_idx = 1;
				}
			} else if (last_idx == 1) {
				if (ab[0] > 0) {
					ab[0]--;
					last_idx = 0;
				}
			} else if (ab[1] > 0) {
				ab[1]--;
				last_idx = 1;
			} else {
				ab[0]--;
				last_idx = 0;
			}
		} else {
			last_idx = -1;
		}
	}
	cout << was-ab[0]-ab[1] << endl;
	return 0;
}
