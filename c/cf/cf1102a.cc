#include <iostream>
/* CodeForces CF1102A problem */
using namespace std;

int main(int argc, char **argv) {
	int64_t n;
	cin >> n;
	int64_t sum = (n+1)*n/2;
	if (sum & 1)
		cout << 1 << endl;
	else
		cout << 0 << endl;
	return 0;
}
