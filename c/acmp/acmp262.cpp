/* ACMP 262 */
#include <stdio.h>
#include <queue>
#include <cinttypes>

using namespace std;

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	priority_queue<uint64_t, vector<uint64_t>, greater<uint64_t>> qq;
	for (int i=0; i<n; i++) {
		int a;
		scanf("%d", &a);
		qq.push(a);
	}
	uint64_t ans = 0;
	while (qq.size() > 1) {
		uint64_t s = qq.top();
		//fprintf(stderr, "%lld + ", s);
		qq.pop();
		s += qq.top();
		//fprintf(stderr, "%lld = %lld\n", qq.top(), s);
		qq.pop();
		ans += s;
		qq.push(s);
	}
	uint64_t fperc = ans*5;
	printf("%.02lf\n", ((double)fperc)/100.0);
	return 0;
}
