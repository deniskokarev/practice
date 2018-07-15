#include <iostream>
/* ACMP 301 */
using namespace std;

int main(int argc, char **argv) {
	int s, k;
	cin >> s >> k;
	string mn(k, '0');
	string mx(k, '0');
	mx[0] = mn[0] = '1';
	s--;
	// mx
	int c = s;
	for (int i=0; i<k && c>0; i++) {
		while (c>0 && mx[i] < '9') {
			mx[i]++;
			c--;
		}
	}
	// mn
	c = s;
	for (int i=k-1; i>=0 && c>0; i--) {
		while (c>0 && mn[i] < '9') {
			mn[i]++;
			c--;
		}
	}
	cout << mx << ' ' << mn << endl;
	return 0;
}
