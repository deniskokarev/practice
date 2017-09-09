/* ACMP 946 */

#include <iostream>
#include <list>
#include <cassert>

using namespace std;

int main(int argc, char **argv) {
	list<int> ss;
	int n;
	cin >> n;
	while (n-- > 0) {
		int op;
		int d;
		cin >> op;
		switch (op) {
		case 1:
			cin >> d;
			ss.push_front(d);
			break;
		case 2:
			cin >> d;
			ss.push_back(d);
			break;
		case 3:
			d = ss.front();
			ss.pop_front();
			cout << d << endl;
			break;
		case 4:
			d = ss.back();
			ss.pop_back();
			cout << d << endl;
			break;
		default:
			assert(false && "Incorrect operation");
		}
	}
	return 0;
}
