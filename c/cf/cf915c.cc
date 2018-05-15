#include <iostream>
#include <algorithm>
#include <numeric>
/* CodeForces CF915C problem */
using namespace std;

int main(int argc, char **argv) {
	int64_t a, b;
	cin >> a >> b;
	int64_t ans = a;
	int64_t dd[20];
	int64_t p10[20];
	int len=0;
	int64_t p=1;
	while (a>0) {
		dd[len] = a%10;
		a /= 10;
		p10[len] = p;
		p *= 10;
		len++;
	}
	sort(dd, dd+len, std::greater<int64_t>());
	int hp = len-1;
	for (int lp=0; lp<hp; lp++) {
		if (dd[lp] != 0) {
			int64_t dd2[20];
			copy(dd, dd+len, dd2);
			swap(dd2[lp], dd2[hp]);
			sort(dd2, dd2+hp, std::greater<int64_t>());
			int64_t res = inner_product(dd2, dd2+len, p10, int64_t(0));
			if (res <= b) {
				copy(dd2, dd2+len, dd);
				ans = res;
				break;
			}
		}
	}
	for (hp=len-2; hp>=0; hp--) {
		for (int lp=0; lp<hp; lp++) {
			int64_t dd2[20];
			copy(dd, dd+len, dd2);
			swap(dd2[lp], dd2[hp]);
			sort(dd2, dd2+hp, std::greater<int64_t>());
			int64_t res = inner_product(dd2, dd2+len, p10, int64_t(0));
			if (res <= b) {
				copy(dd2, dd2+len, dd);
				ans = res;
				break;
			}
		}
	}
	cout << ans << endl;
	return 0;
}
