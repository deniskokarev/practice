#include <iostream>
#include <iomanip>
#include <cmath>
/* Hackerrank https://www.hackerrank.com/challenges/s10-poisson-distribution-1/problem */
using namespace std;

/**
 * factorial n!
 */
uint64_t fact(int n) {
	uint64_t res = 1;
	while (n>1)
		res *= n--;
	return res;
}

int main(int argc, char **argv) {
	double lambda = 2.5;
	int k = 5;
	cout << setprecision(3) << fixed << pow(lambda,k)*exp(-lambda)/double(fact(k)) << endl;
	return 0;
}
