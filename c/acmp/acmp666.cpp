#include <iostream>
/* ACMP 666 */
using namespace std;

char get_let(unsigned n, int step, unsigned *len) {
	if (n == 0) {
		return 'a'+step;
	} else {
		if (n>len[step])
			return get_let(n-len[step]/2-1, step-1, len);
		else
			return get_let(n-1, step-1, len);
	}
}

int main(int argc, char **argv) {
	unsigned n;
	cin >> n;
	unsigned len[26];
	len[0] = 1;
	for (int i=1; i<26; i++)
		len[i] = len[i-1]*2+1;
	cout << get_let(n-1, 25, len) << endl;
	return 0;
}
