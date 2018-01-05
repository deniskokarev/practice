/* ACMP 15 */
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int cnt = 0;
	for (int i=0; i<n*n; i++) {
		int a;
		cin >> a;
		cnt += (a==1)?1:0;
	}
	cout << cnt/2 << endl;
	return 0;
}
