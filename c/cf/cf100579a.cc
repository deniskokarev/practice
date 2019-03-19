#include <iostream>
#include <vector>
#include <array>
/* CodeForces https://codeforces.com/gym/100579 A problem */
using namespace std;

constexpr int MXSZ = 1e7+1;
constexpr int MXN = 24;

using PC = array<int, MXN>;

int main(int argc, char **argv) {
	vector<uint8_t> is_prime(MXSZ, 1);
	vector<uint8_t> nfact(MXSZ);
	vector<PC> cntfact(MXSZ);
	for (int i=2; i<MXSZ; i++)
		for (int j=i+i; j<MXSZ; j+=i)
			is_prime[j] = 0;
	for (int i=2; i<MXSZ; i++)
		if (is_prime[i])
			for (int j=i; j<MXSZ; j+=i)
				nfact[j]++;
	for (int i=1; i<MXSZ; i++) {
		for (int j=0; j<MXN; j++) {
			cntfact[i] = cntfact[i-1];
			cntfact[i][nfact[i]]++;
		}
	}
	int t;
	cin >> t;
	for (int i=1; i<=t; i++) {
		int a, b, k;
		cin >> a >> b >> k;
		int ans;
		if (k<MXN)
			ans = cntfact[b][k] - cntfact[a-1][k];
		else
			ans = 0;
		cout << "Case #" << i << ": " << ans << "\n";
	}
	return 0;
}
