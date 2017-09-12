/* ACMP 505 */
#include <unordered_map>
#include <string>
#include <stdio.h>

using namespace std;

char buf[1048576];

int main(int argc, char **argv) {
	int l, m, n;
	scanf("%d%d%d", &l, &m, &n);
	unordered_map<string, int> ttmap;
	for (int i=0; i<m; i++) {
		int id;
		char *s = buf;
		char nl;
		scanf("%d %1048576[^\n]%c", &id, s, &nl);
		ttmap[s] = id;
	}
	int ok=0, bad=0;
	for (int i=0; i<n; i++) {
		char *s = buf;
		char nl;
		scanf("%1048576[^\n]%c", s, &nl);
		auto fnd = ttmap.find(s);
		if (fnd != ttmap.end()) {
			printf("%d\n", fnd->second);
			ok++;
		} else {
			printf("-\n");
			bad++;
		}
	}
	printf("OK=%d BAD=%d\n", ok, bad);
	return 0;
}
