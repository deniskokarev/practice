/* ACMP 1072 */
#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int links[n];
	fill(links, links+n, 0);
	for (int i=0; i<n-1; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		links[a]++;
		links[b]++;
	}
	int cnt=0;
	for (auto l:links)
		cnt += (l>1);
	cout << cnt << endl;
	return 0;
}
