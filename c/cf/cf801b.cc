#include <iostream>
/* CodeForces CF801B problem */
using namespace std;

int main(int argc, char **argv) {
	string x, y;
	cin >> x >> y;
	string z(x.length(), ' ');
	int i;
	for (i=0; i<x.length(); i++) {
		if (y[i] > x[i])
			break;
		else
			z[i] = y[i];
	}
	if (i<x.length())
		cout << -1;
	else	
		cout << z;
	cout << endl;
	return 0;
}
