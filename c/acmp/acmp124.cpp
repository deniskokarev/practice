/* ACMP 124 */
#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char **argv) {
	int n, m;
	cin >> n >> m;
	int cc[n];
	fill(cc, cc+n, 0);
	while(m-- > 0) {
		int i, j;
		cin >> i >> j;
		i--, j--;
		cc[i]++, cc[j]++;
	}
	for (auto c:cc)
		cout << c << ' ';
	cout << endl;
	return 0;
}
