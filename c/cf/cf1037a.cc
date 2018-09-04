#include <iostream>
#include <cmath>
/* CodeForces CF1037A problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	cout << int(ceil(log2(n+1))) << endl;
	return 0;
}
