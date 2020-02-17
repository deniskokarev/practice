#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
/* CodeForces CF1213A problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int cnt[2] {0, 0};
	while (n--) {
		int a;
		cin >> a;
		int o = a&1;
		cnt[o]++;
	}
	cout << min(cnt[0], cnt[1]) << endl;
	return 0;
}
