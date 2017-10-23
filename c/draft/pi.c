#include <stdio.h>
#include <math.h>

int main(int argc, char **argv) {
	const double r = 10000000;
	double l = r/sqrt(2);
	double h = l;
	int p2 = 4;
	// start with inscribed square
	for (int i=0; i<20; i++,p2*=2) {
		// and double sides with each step
		fprintf(stderr, "sides=%d, pi=%.12f\n", p2, l*p2/r);
		l = sqrt((r-h)*(r-h)+l*l)/2;
		h = sqrt(r*r-l*l);
	}
	printf("pi=%.12f\n", l*p2/r);
	return 0;
}
