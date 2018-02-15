#include <iostream>
#include <cstdio>
#include <cstring>

/* CodeForces CF916A problem */
using namespace std;

bool is_lucky(int mm) {
	int h = mm/60;
	int m = mm%60;
	char stm[6];
	snprintf(stm, 6, "%02d%02d", h, m);
	return (strchr(stm, '7') != nullptr);
}

int main(int argc, char **argv) {
	int x;
	int h, m;
	cin >> x >> h >> m;
	int mm = h*60+m;
	int ml = mm;
	int ans = 0;
	while (!is_lucky(ml)) {
		ans++;
		ml += 60*24;
		ml -= x;
		ml %= 60*24;
	}
	cout << ans << endl;
	return 0;
}
