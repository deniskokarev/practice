#include <iostream>
#include <vector>
#include <list>
/* CodeForces CF999C problem */
using namespace std;

int main(int argc, char **argv) {
	int n, k;
	cin >> n >> k;
	string s;
	cin >> s;
	vector<list<int>> pos(256, list<int>());
	for (int i=0; i<n; i++)
		pos[s[i]].push_back(i);
	int let = 'a';
	while (k--) {
		while (pos[let].empty())
			let++;
		s[pos[let].front()] = '.';
		pos[let].pop_front();
	}
	for (char c:s)
		if (c != '.')
			cout << c;
	cout << endl;
	return 0;
}
