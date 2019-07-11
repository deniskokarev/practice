#include <cstdio>
#include <vector>
/* CodeForces CF1119A problem */
using namespace std;

struct P {
	int f, t;
};

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	vector<int> cc(n+2);
	for (int i=1; i<=n; i++)
		scanf("%d", &cc[i]);
	vector<P> cpos(n+1, P {-1,-1});
	for (int i=1; i<=n; i++) {
		if (cc[i] != cc[i+1])
			cpos[cc[i]].t = i;
		if (cc[i-1] != cc[i])
			cpos[cc[i]].f = i;
	}
	int mx = 0;
	for (int i=1; i<=n; i++) {
		if (cpos[cc[i]].t == n)
			mx = max(mx, cpos[cc[i]].f-1 - i);
		else
			mx = max(mx, n - i);
	}
	printf("%d\n", mx);
	return 0;
}
