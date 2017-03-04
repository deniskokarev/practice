#include <iostream>
/* CodeForces CF272B problem */

using namespace std;

int nbits(int i) {
	int rc;
	for (rc = 0; i>0; i>>=1)
		rc += i & 0x1;
	return rc;
}

int bbuck[32];

int main(int argc, char **argv) {
	int n;
	cin >> n;
	for (int i=0; i<n; i++) {
		int a;
		cin >> a;
		bbuck[nbits(a)]++;
	}
	int64_t res = 0;
	for (int i=0; i<32; i++) {
		int64_t b = bbuck[i];
		if (b > 1)
			res += b*(b-1)/2;
	}
	cout << res << endl;
}
