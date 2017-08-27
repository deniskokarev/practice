/* ACMP 184 */
#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int months[13] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};

int main() {
	int k;
	scanf("%d", &k);
	int tt[k];
	for (auto &t:tt) {
		int mh, d, h, mn;
		scanf("%d.%d. %d:%d", &d, &mh, &h, &mn);
		t = mn+h*60+(months[mh-1]+d)*24*60;
	}
	sort(tt, tt+k);
	int ans = 0;
	for (int i=0; i<k-1; ++i,++i) {
		int d = tt[i+1]-tt[i]; 
		ans += (d/24/60)*8*60+d%(8*60)+1;
	}
	printf("%d:%02d\n", ans/60, ans%60);
}

