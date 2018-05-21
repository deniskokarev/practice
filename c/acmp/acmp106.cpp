#include <iostream>
/* ACMP 106 */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int cnt[2] {0};
	while (n--) {
		int a;
		cin >> a;
		cnt[a&1]++;
	}
	cout << min(cnt[0], cnt[1]) << endl;
	return 0;
}
