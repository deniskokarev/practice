#include <iostream>
/* CodeForces CF1036A problem */
using namespace std;

int main(int argc, char **argv) {
	int64_t n, k;
	cin >> n >> k;
	cout << k/n+(k%n!=0) << endl;
	return 0;
}
