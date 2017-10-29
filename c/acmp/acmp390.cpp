/* ACMP 390 */
#include <cstdio>
#include <cmath>
#include <cinttypes>

using namespace std;

struct P {
	int64_t x, y;
	int64_t cross(const P &b) const {
		return x*b.y-y*b.x;
	}
	P operator-(const P&b) const {
		P c {x, y};
		c.x -= b.x;
		c.y -= b.y;
		return c;
	}
	long double len() const {
		return sqrtl(x*x+y*y);
	}
};

int main(int argc, char **argv) {
	P pp[3];
	P c;
	for (auto &p:pp) {
		scanf("%lld%lld", &p.x, &p.y);
		p.x *= 1e3;
		p.y *= 1e3;
	}
	scanf("%lld%lld", &c.x, &c.y);
	c.x *= 1e3;
	c.y *= 1e3;
	long double mn = 1e17;
	for (int i=0; i<2; i++) {
		int np = (i+1)%3;
		long double s2 = fabsl((long double)((pp[i]-c).cross(pp[np]-c)));
		long double h = s2/(pp[np]-pp[i]).len();
		mn = (mn>h)?h:mn;
	}
	printf("%.7f\n", double(mn/1e3));
	return 0;
}
