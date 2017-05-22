#include <iostream>
/* CodeForces CF808A problem */
using namespace std;

int64_t p10(int p) {
	int64_t n = 1;
	while (p>0) {
		n *= 10;
		p--;
	}
	return n;
}

int main(int argc, char **argv) {
	int64_t n;
	cin >> n;
	string a;
	int l=0;
	int64_t n1 = n;
	while (n1>0) {
		a[l] = n1%10;
		n1 /= 10;
		l++;
	}
	int64_t ans = (a[l-1]+1)*p10(l-1)-n;
	cout << ans << endl;
	return 0;
}
