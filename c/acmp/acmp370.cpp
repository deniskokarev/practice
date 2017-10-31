/* ACMP 370 */
#include <cstdio>
#include <cmath>

using namespace std;

struct P {
	double x, y;
	double cross(const P &b) const {
		return x*b.y - y*b.x;
	}
};

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	P vv[n];
	for (auto &v:vv)
		scanf("%lf%lf", &v.x, &v.y);
	double s = 0;
	for (int i=0; i<n; i++) {
		int j = (i+1)%n;
		s += vv[i].cross(vv[j]);
	}
	printf("%.1f\n", fabs(s/2));
	return 0;
}
