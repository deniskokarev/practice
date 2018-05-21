#include <iostream>
/* ACMP 149 */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int vv[n];
	int i = n;
	while (i--) {
		int a;
		cin >> a;
		vv[i] = a;
	}
	for (auto a:vv)
		cout << a << ' ';
	cout << endl;
	return 0;
}
