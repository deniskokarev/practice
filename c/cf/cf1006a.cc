#include <iostream>
/* CodeForces CF1006A problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	while (n--) {
		int a;
		cin >> a;
		a -= ((a&1)==0);
		cout << a << ' ';
	}
	cout << endl;
	return 0;
}
