/* ACMP 822 */
#include <stdio.h>
#include <math.h>

struct V {
	int x, y;
	void operator -=(const V &v) {
		x -= v.x;
		y -= v.y;
	}
};

int main(int argc, char **argv) {
	V p[3];
	fscanf(stdin, "%d%d%d%d%d%d", &p[0].x, &p[0].y, &p[1].x, &p[1].y, &p[2].x, &p[2].y);
	p[1] -= p[0];
	p[2] -= p[0];
	double a = fabs((p[1].x*p[2].y - p[2].x*p[1].y)/2.0);
	printf("%0.1f\n", a);
	return 0;
}
