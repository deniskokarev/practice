#include <iostream>

using namespace std;

#define T long

inline T gcd(T a, T b) {
	while (true) {
		if (a>b) {
			a = a%b;
			if (a == 0)
				return b;
		} else {
			b = b%a;
			if (b == 0)
				return a;
		}
	}
}

inline T lcm(T a, T b) {
	return a/gcd(a,b)*b;
}

int main(int args, char **argv) {
	int n, m, z;
	cin >> n >> m >> z;
	cout << z/lcm(n, m) << endl;
}
