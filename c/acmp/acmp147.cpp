/* ACMP 147 */
#include <iostream>
using namespace std;
int main() {
	int n;
	cin >> n;
	int f1=0, f2=1;
	for (;n>0;--n) {
		int f = f1+f2;
		f1 = f2;
		f2 = f;
	}
	cout << f1 << endl;
}

