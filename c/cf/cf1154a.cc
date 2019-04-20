#include <iostream>
#include <algorithm>
/* CodeForces CF1154A problem */
using namespace std;

int main(int argc, char **argv) {
	int ss[4];
	cin >> ss[0] >> ss[1] >> ss[2] >> ss[3];
	sort(ss, ss+4);
	for (int i=0; i<3; i++)
		cout << ss[3] - ss[i] << ' ';
	cout << endl;
	return 0;
}
