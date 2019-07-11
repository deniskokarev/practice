#include <cstdio>
#include <vector>
/* CodeForces CF1143A problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	vector<int> dd(n);
	int ss[2] = {0, 0};
	for (auto &d:dd) {
		scanf("%d", &d);
		ss[d]++;
	}
	int i;
	for (i=0; i<n; i++) {
		auto d = dd[i];
		ss[d]--;
		if (!ss[d])
			break;
	}
	printf("%d\n", i+1);
	return 0;
}
