#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdio>
/* CodeForces CF808B problem */
using namespace std;

int main(int argc, char **argv) {
	int k, n;
	cin >> n >> k;
	vector<int> aa(n);
	for (int i=0; i<n; i++)
		cin >> aa[i];
	int i = 0;
	int64_t s = 0;
	for (i=0; i<k; i++)
		s += aa[i];
	int64_t ss = s;
	for (; i<n; i++) {
		s -= aa[i-k];
		s += aa[i];
		ss += s;
	}
	fprintf(stdout, "%.7f\n", ((double)ss)/((double)n-k+1));
	return 0;
}
