#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
/* CodeForces CF1216A problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	string s;
	cin >> n >> s;
	int cnt = 0;
	for (int i=0; i<s.size(); i+=2) {
		if (s[i] == s[i+1]) {
			s[i+1] = (s[i] == 'a')+'a';
			cnt++;
		}
	}
	cout << cnt << endl;
	cout << s << endl;
	return 0;
}
