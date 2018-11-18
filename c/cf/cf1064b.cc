#include <iostream>
/* CodeForces CF1064B problem */
using namespace std;

int main(int argc, char **argv) {
	int t;
	cin >> t;
	while (t--) {
		int a;
		cin >> a;
		int ans = 1<<30;
		int x = a;
		for (int i=0,p2=1; i<30; i++,p2<<=1) {
			if (!(x & p2)) {
				int o = x ^ p2;
				if ((o - a) == (o ^ a))
					ans /= 2;
			}
		}
		cout << ans << endl;
	}
	return 0;
}
