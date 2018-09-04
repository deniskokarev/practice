#include <iostream>
/* CodeForces CF1003B problem */
using namespace std;

int main(int argc, char **argv) {
	int a, b, x;
	cin >> a >> b >> x;
	string s(a+b, ' ');
	int na = a, nb = b;
	int p = 0;
	for (int i=0; i<x-1; i++) {
		s[p++] = '0';
		na--;
		s[p++] = '1';
		nb--;
	}
	if (nb > 0 && na > 0) {
		for (int j=0; j<nb; j++)
			s[p++] = '1';
		for (int j=0; j<na; j++)
			s[p++] = '0';
		cout << s << endl;
		return 0;
	}
	na = a, nb = b;
	p = 0;
	for (int i=0; i<x-1; i++) {
		s[p++] = '1';
		nb--;
		s[p++] = '0';
		na--;
	}
	for (int j=0; j<na; j++)
		s[p++] = '0';
	for (int j=0; j<nb; j++)
		s[p++] = '1';
	cout << s << endl;
	return 0;
}
