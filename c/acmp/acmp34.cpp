#include <iostream>
#include <cstring>
/* ACMP 34 */
using namespace std;

int main(int argc, char **argv) {
	int n, k;
	cin >> n >> k;
	string s;
	cin >> s;
	int w = 0;
	int hsz = 1;
	for (int i=0; i<k; i++) {
		w *= 10;
		w += s[i]-'0';
		hsz *= 10;
	}
	char hash[hsz];
	memset(hash, 0, hsz);
	hash[w] = 1;
	string ans = "NO";
	int hi = hsz/10;
	for (int i=k; i<n; i++) {
		w -= hi*(s[i-k]-'0');
		w *= 10;
		w += s[i]-'0';
		if (hash[w])
			ans = "YES";
		hash[w] = 1;
	}
	cout << ans << endl;
	return 0;
}
