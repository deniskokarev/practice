#include <iostream>
#include <cassert>
/* ACMP 52 */
using namespace std;

int main(int argc, char **argv) {
	string n;
	cin >> n;
	assert(n.length()==6);
	int l = n[0]+n[1]+n[2];
	int r = n[3]+n[4]+n[5];
	cout << (l==r?"YES":"NO") << endl;
	return 0;
}
