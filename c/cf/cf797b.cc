#include <iostream>
#include <algorithm>

/* CodeForces CF797B problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int aa[n];
	int64_t s = 0;
	for (auto &a:aa) {
		cin >> a;
		s += a;
	}
	sort(aa, aa+n);
	if ((s&1)==0) {
		int i;
		for (i=0; i<n && (aa[i]&1)==0; i++);
		s -= aa[i];
		aa[i] = 0;
	}
	int lso = 0;
	for (int i=0; i<n; i++) {
		if (aa[i]<0) {
			if ((aa[i]&1)==0) {
				s -= aa[i];
			} else {
				if (lso&1) {
					s -= lso+aa[i];
					lso = 0;
				} else {
					lso = aa[i];
				}
			}
		} else {
			if ((aa[i]&1)==1 && (lso&1) && lso+aa[i] < 0) {
				s -= lso+aa[i];
				lso = 0;
			}	
		}
	}
	cout << s << endl;
	return 0;
}
