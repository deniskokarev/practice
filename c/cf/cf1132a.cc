#include <iostream>
/* CodeForces CF1132A problem */
using namespace std;

int main(int argc, char **argv) {
	int nll, nlr, nrl, nrr;
	cin >> nll >> nlr >> nrl >> nrr;
	int ans = ((nll == nrr) && (!nrl || nll));
	cout << ans << endl;
	return 0;
}
