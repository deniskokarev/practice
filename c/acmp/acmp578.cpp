#include <iostream>
/* ACMP 578 */
using namespace std;

int base3(int n, int dd[]) {
	int p=0;
	while (n>0) {
		dd[p++] = n%3;
		n/=3;
	}
	return p;
}

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int dd[32] {0};
	int l = base3(n, dd);
	int i;
	for (i=0; i<l; i++) {
		if (dd[i] < 1) {
			dd[i] += 3;
			dd[i+1]--;
		}
	}
	for (i=31; i>=0 && dd[i]==0; i--);
	for (; i>=0; i--)
		cout << dd[i];
	cout << endl;
	return 0;
}
