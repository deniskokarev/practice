#include <iostream>
/* CodeForces CF1065A problem */
using namespace std;

int main(int argc, char **argv) {
	int t;
	cin >> t;
	while (t--) {
		int s, a, b, c;
		cin >> s >> a >> b >> c;
		int64_t n = s/c;
		int64_t p = n/a*b;
		cout << n+p << '\n';
	}
	return 0;
}
