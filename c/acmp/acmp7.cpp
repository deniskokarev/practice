/* ACMP 7 problem */

#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char **argv) {
	pair<int,string> nn[3];
	for (int i=0; i<3; i++) {
		cin >> nn[i].second;
		nn[i].first = nn[i].second.length();
	}
	sort(nn, nn+3);
	cout << nn[2].second << endl;
	return 0;
}
