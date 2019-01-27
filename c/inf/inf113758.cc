#include <iostream>
#include <cmath>
/* informatics Reg2018 1 b https://informatics.msk.ru/mod/statements/view3.php?id=30793&chapterid=113758#1 */
using namespace std;

inline int64_t nsqrt(long double b, long double e) {
	if (b>0)
		return int64_t(std::sqrt(e-1)) - int64_t(std::sqrt(b-1));
	else
		return int64_t(std::sqrt(e-1));
}

int main(int argc, char **argv) {
	int64_t a, b, k;
	cin >> a >> b >> k;
	long double ad = a;
	long double bd = b;
	int64_t f = ceil(std::cbrt(ad));
	int64_t t = floor(std::cbrt(bd));
	int64_t ans = 0;
	for (int64_t y=f; y<=t; y++)
		ans += nsqrt(y*y*y-k, y*y*y+k+1);
	cout << ans << endl;
	return 0;
}
