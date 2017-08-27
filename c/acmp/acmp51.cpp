#include <iostream>
/* ACMP 51 */
using namespace std;

int main(int argc, char **argv) {
	uint64_t n;
	cin >> n;
	string bang;
	cin >> bang;
	uint64_t k = bang.size();
	uint64_t ans = 1;
	while (n>k) {
		ans *= n;
		n -= k;
	}
	if (n == k)
		ans *= k;
	else
		ans *= n;
	cout << ans << endl;
	return 0;
}

