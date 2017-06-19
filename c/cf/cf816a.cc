#include <iostream>
//#include <stdlib.h>
//#include <stdio.h>
/* CodeForces CF816A problem */
using namespace std;

int main(int argc, char **argv) {
	int hh, mm;
	string s;
	cin >> s;
	sscanf(s.c_str(), "%d:%d", &hh, &mm);
	int mmm = mm+hh*60;
	int i;
	for (i=0; i<60*24; i++) {
		char r[32];
		int m = (mmm+i)%60;
		int h = ((mmm+i)/60)%24;
		snprintf(r, 32, "%02d%02d", h, m);
		if (r[3] == r[0] && r[2] == r[1])
			break;
	}
	cout << i << endl;
	return 0;
}
