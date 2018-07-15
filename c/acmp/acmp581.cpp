#include <cstdio>
#include <cstring>
#include <cstdint>
#include <numeric>
/* ACMP 581 */
using namespace std;

struct P {
	int x, y;
	int cross(const P &b) const {
		return x*b.y - y*b.x;
	}
};

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	P p1, p2;
	scanf("%d%d%d%d", &p1.x, &p1.y, &p2.x, &p2.y);
	int ans[n];
	for (int i=0; i<n; i++) {
		P p;
		int r;
		scanf("%d%d%d", &p.x, &p.y, &r);
		P va = P {p1.x-p.x, p1.y-p.y};
		P vb = P {p2.x-p.x, p2.y-p.y};
		int64_t s2_2 = va.cross(vb);
		s2_2 *= s2_2;
		int64_t s1_2 = (p2.x-p1.x)*(p2.x-p1.x) + (p2.y-p1.y)*(p2.y-p1.y);
		s1_2 *= r*r;
		ans[i] = (s1_2 >= s2_2);
	}
	printf("%d\n", accumulate(ans, ans+n, 0));
	for (int i=0; i<n; i++)
		if (ans[i])
			printf("%d ", i+1);
	printf("\n");
	return 0;
}
