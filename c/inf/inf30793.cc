#include <iostream>
/* informatics Reg1 https://informatics.msk.ru/mod/statements/view.php?id=30793#1 */
using namespace std;

int main(int argc, char **argv) {
	int64_t a, b, c;
	cin >> a >> b >> c;
	int64_t ans = (3*a+b-c+2)/3;
	if (ans < 0)
		ans = 0;
	cout << ans << endl;
	return 0;
}
