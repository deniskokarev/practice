#include <iostream>
/* CodeForces CF798C problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int aa[n];
	for (auto &a:aa)
		cin >> a;
	int s = 0;
	for (int i=0; i<n; i++) {
		if ((aa[i]&1) == 1) {
			if (i+1<n && (aa[i+1]&1) == 1) {
				i++;
				s++;
			} else {
				s = -1;
				break;
			}
		}
	}
	if (s < 0)
		cout << "NO" << endl;
	else
		cout << "YES" << endl << s << endl;
	return 0;
}
