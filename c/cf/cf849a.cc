#include <iostream>

/* CodeForces CF849A problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int aa[n];
	for (auto &a:aa)
		cin >> a;
	bool ans;
	if ((aa[0]&1)==0 || (aa[n-1]&1)==0) {
		ans = false;
	} else if ((n&1)) {
		ans = true;
	} else {
		int cuts = 0;
		int ln = 1;
		int lcut = 0;
		for (int i=0; i<n-1; i++,ln++) {
			if (aa[i]&1 && aa[i+1]&1 && ln&1) {
				cuts++;
				ln=0;
				lcut = i;
			}
		}
		if (cuts > 0 && lcut < n-1 && ((n-1-lcut)&1)==0)
			cuts--;
		ans = (cuts>1) && ((cuts&1)==0);
	}
	cout << (ans?"Yes":"No") << endl;
	return 0;
}
