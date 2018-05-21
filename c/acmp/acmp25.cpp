#include <iostream>
/* ACMP 25 */
using namespace std;

int main(int argc, char **argv) {
	int a, b;
	char out[] = "<=>";
	cin >> a >> b;
	char ans = out[(a>b)-(a<b)+1];
	cout << ans << endl;
	return 0;
}
