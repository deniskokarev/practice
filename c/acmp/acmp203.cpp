/* ACMP 203 */
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	string sk;
	string sd;
	cin >> sk >> sd;
	string sdsd = sd+sd;
	auto p = sdsd.find(sk);
	if (p != string::npos)
		cout << p << endl;
	else
		cout << -1 << endl;
	return 0;
}
