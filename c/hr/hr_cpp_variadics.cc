/* Hackerrank https://www.hackerrank.com/challenges/cpp-variadics */
#include <iostream>
using namespace std;

// Enter your code for reversed_binary_value<bool...>()
/* Hackerrank https://www.hackerrank.com/challenges/cpp-variadics */

template<bool h, bool... t> struct _reversed_binary_value {
    static constexpr int val = h + (_reversed_binary_value<t...>::val << 1);
};

template<> struct _reversed_binary_value<true> {
    static constexpr int val = 1;
};

template<> struct _reversed_binary_value<false> {
    static constexpr int val = 0;
};

template<bool... digits> constexpr int reversed_binary_value() {
    return _reversed_binary_value<digits...>::val;
}

template <int n, bool...digits>
struct CheckValues {
  	static void check(int x, int y)
  	{
    	CheckValues<n-1, 0, digits...>::check(x, y);
    	CheckValues<n-1, 1, digits...>::check(x, y);
  	}
};

template <bool...digits>
struct CheckValues<0, digits...> {
  	static void check(int x, int y)
  	{
    	int z = reversed_binary_value<digits...>();
    	std::cout << (z+64*y==x);
  	}
};

int main()
{
  	int t; std::cin >> t;

  	for (int i=0; i!=t; ++i) {
		int x, y;
    	cin >> x >> y;
    	CheckValues<6>::check(x, y);
    	cout << "\n";
  	}
}
