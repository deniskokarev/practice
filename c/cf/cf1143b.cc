#include <iostream>
#include <algorithm>
/* CodeForces CF1143B problem */
using namespace std;

int main(int argc, char **argv) {
	unsigned n;
	cin >> n;
	unsigned dd[32];
	int len,i;
	dd[0] = 1;
	for (len=1,i=n; i>0; i/=10,len++)
		dd[len] = i%10;
	dd[len++] = 1;
	unsigned pl[32];
	copy(dd, dd+32, pl);
	for (int i=len-2; i>=0; i--)
		pl[i] *= pl[i+1];
	unsigned pr[32];
	copy(dd, dd+32, pr);
	for (int i=1; i<len; i++)
		pr[i] *= pr[i-1];
	unsigned p9[11] = {1, 9, 9*9, 9*9*9, 9*9*9*9, 9*9*9*9*9, 9*9*9*9*9*9, 9*9*9*9*9*9*9, 9*9*9*9*9*9*9*9, 9*9*9*9*9*9*9*9*9, 9*9*9*9*9*9*9*9*9*9U};
	unsigned ans = 0;
	for (int i=len-2; i>0; i--) {
		ans = max(ans, pl[i+1]*dd[i]*pr[i-1]);
		if (dd[i] > 1) {
			ans = max(ans, pl[i+1]*(dd[i]-1)*p9[i-1]);
		} else if (dd[i] == 1) {
			//cerr << "first1 i=" << i << " prod=" << p9[i-1] << endl;
			ans = max(ans, p9[i-1]);
		}
	}
	cout << ans << endl;
	return 0;
}
