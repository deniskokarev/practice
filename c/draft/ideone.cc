/**
 * Template for ideone problem
 * http://ideone.com/xHX9U2
 */
#include <vector>
#include <iostream>

int result(const std::vector<int> &a) {
	return a.size();
}

int main(int argc, char **argv) {
	std::vector<int> a;
	int n;
	while(std::cin >> n)
		a.push_back(n);
	std::cout << result(a) << std::endl;
}
