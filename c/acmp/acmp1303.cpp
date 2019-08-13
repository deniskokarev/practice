#include <iostream>
#include <vector>
/* ACMP 1303 */
using namespace std;

int main(int argc, char **argv) {
	int n;
	string s;
	cin >> n;
	cin >> s;
	vector<int> stack;
	stack.reserve(n+1);
	bool ans = true;
	vector<char> map(256);
	map[')'] = '(';
	map['}'] = '{';
	map[']'] = '[';
	for (char c:s) {
		switch (c) {
		case '(':
		case '{':
		case '[':
			stack.push_back(c);
			break;
		default:
			if (stack.back() == map[c])
				stack.pop_back();
			else
				ans = false;
		}
	}
	ans &= stack.size() == 0;
	cout << (ans?"Yes":"No") << endl;
	return 0;
}
