#include <iostream>
#include <cstring>
/* CodeForces CF1003A problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int cnt[101];
	memset(cnt, 0, sizeof(cnt));
	int mx = 0;
	while (n--) {
		int a;
		cin >> a;
		cnt[a]++;
		mx = max(mx, cnt[a]);
	}
	cout << mx << endl;
	return 0;
}
