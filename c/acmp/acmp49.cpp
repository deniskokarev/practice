#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

/* ACMP 49 */
using namespace std;

const map<char, const vector<int>> mp {
	{'0', {0}},
	{'1', {1}},
	{'2', {2}},
	{'3', {3}},
	{'4', {4}},
	{'5', {5}},
	{'6', {6}},
	{'7', {7}},
	{'8', {8}},
	{'9', {9}},
	{'a', {0, 1, 2, 3}},
	{'b', {1, 2, 3, 4}},
	{'c', {2, 3, 4, 5}},
	{'d', {3, 4, 5, 6}},
	{'e', {4, 5, 6, 7}},
	{'f', {5, 6, 7, 8}},
	{'g', {6, 7, 8, 9}},
	{'?', {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}}
};

int main(int argc, char **argv) {
	string p1, p2;
	cin >> p1 >> p2;
	unsigned ans = 1;
	for (int i=0; i<p1.length(); i++) {
		vector<int> intersect;
		set_intersection(mp.at(p1[i]).cbegin(),mp.at(p1[i]).cend(),mp.at(p2[i]).cbegin(),mp.at(p2[i]).cend(), back_inserter(intersect));
		ans *= intersect.size();
	}
	cout << ans << endl;
	return 0;
}
