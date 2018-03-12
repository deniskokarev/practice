#include <iostream>
#include <algorithm>
/* CodeForces CF915C problem */

int main(int argc, char **argv) {
	std::string a, b;
	std::cin >> a >> b;
	std::sort(a.begin(), a.end(), std::greater<char>());
	std::string o(a);
	if (b.length() == a.length()) {
		int i=0,j=0;
		while (i<b.size() && j<a.length()) {
			for (j=0; j<a.length(); j++) {
				if (a[j] == b[i]) {
					o[i++] = a[j];
					a[j] = '\127';
					break;
				} else if (a[j] < b[i]) {
					o[i++] = a[j];
					a[j] = '\127';
					goto end;
				}
			}
		}
	end:
	    for(int j=0; j<a.size(); j++)
			if (a[j] != '\127')
				o[i++] = a[j];
	}
	std::cout << o << std::endl;
	return 0;
}
