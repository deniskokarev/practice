#include <iostream>
/* ACMP 8 */
using namespace std;

int main(int argc, char **argv) {
	int a, b, c;
	cin >> a >> b >> c;
	const char *ans = (a*b==c)?"YES":"NO";
	cout << ans << endl;
	return 0;
}
