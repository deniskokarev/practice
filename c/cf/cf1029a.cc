#include <iostream>
/* CodeForces CF1029A problem */
using namespace std;

int main(int argc, char **argv) {
	int n, k;
	cin >> n >> k;
	string t;
	cin >> t;
	int psz = 0;
	for (int s=1,l=t.size()-1; l>0; s++,l--) {
		if (t.substr(0,l) == t.substr(s,l)) {
			psz = l;
			break;
		}
	}
	if (psz > 0) {
		cout << t;
		for (int i=1; i<k; i++)
			cout << t.substr(psz, t.size()-psz);
	} else {
		for (int i=0; i<k; i++)
			cout << t;
	}
	cout << endl;
	return 0;
}
