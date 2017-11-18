/* ACMP 1149 */
#include <iostream>
using namespace std;

int main(int argc, char **argv) {
	string n;
	cin >> n;
	int ans = 0;
	for (auto &d:n)
		ans += (d=='0');
	cout << ans << endl;
	return 0;
}
