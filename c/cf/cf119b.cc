#include <iostream>
#include <set>
/* CodeForces CF1119B problem */
using namespace std;

int main(int argc, char **argv) {
	int n, h;
	cin >> n >> h;
	multiset<int,std::greater<int>> hh;
	int ans = 0;
	while (n--) {
		int a;
		cin >> a;
		hh.insert(a);
		int64_t t = 0;
		int p = 0;
		int aa[2];
		for (auto h:hh) {
			aa[p] = h;
			if (p)
				t += max(aa[0], aa[1]);
			p ^= 1;
		}
		if (p)
			t += aa[0];
		if (t <= h)
			ans++;
		else
			break;
	}
	printf("%d\n", ans);
	return 0;
}
