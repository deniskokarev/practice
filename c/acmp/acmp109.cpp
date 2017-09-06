/* ACMP 109 */
#include <cstdio>
#include <cassert>
#include <string>

using namespace std;

unsigned d[1001];	// remainders that we have seen

int main(int argc, char **argv) {
	unsigned a, b;
	scanf("%u/%u", &a, &b);
	assert(a < 1001 && b < 1001);
	printf("%u", a/b);
	unsigned rem = a%b;
	if (rem > 0) {
		string frac;
		int pos = 0;
		while (rem > 0 && d[rem] == 0) {
			d[rem] = pos+1;
			rem *= 10;
			pos++;
			frac.push_back(rem/b+'0');
			rem %= b;
		}
		if (rem == 0)
			printf(".%s", frac.c_str());
		else
			printf(".%s(%s)", frac.substr(0, d[rem]-1).c_str(), frac.substr(d[rem]-1).c_str());
	}
	printf("\n");
	return 0;
}
