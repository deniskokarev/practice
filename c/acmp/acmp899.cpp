/* ACMP 899 */

#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
	string s;
	while (getline(cin, s)) {
		vector<char> stack;
		for (int i=0; i<s.length(); i++) {
			char c = 0;
			switch(s[i]) {
			case '(':
				c++;
			case '{':
				c++;
			case '[':
				c++;
				stack.push_back(c);
				break;
			case ')':
				c++;
			case '}':
				c++;
			case ']':
				c++;
				if (stack.size() > 0 && stack.back() == c)
					stack.pop_back();
				else
					goto err;
				break;
			}
		}
		if (stack.size() == 0) {
			cout << '0';
			continue;
		}
	err:
		cout << '1';
	}
	cout << endl;
	return 0;
}
