#include <iostream>
#include <vector>
/* CodeForces CF1144A problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	for (int i=0; i<n; i++) {
		vector<char> cnt(256);
		string s;
		cin >> s;
		for (unsigned char ch:s)
			cnt[ch]++;
		bool ans = true;
		int fst = -1;
		int lst = -1;
		for (int i='a'; i<='z'; i++) {
			ans &= (cnt[i] == 0 || cnt[i] == 1);
			if (cnt[i] == 1) {
				lst = i;
				if (fst == -1)
					fst = i;
			}
		}
		int sm = 0;
		for (int j=fst; j<=lst; j++)
			sm += cnt[j];
		ans &= (sm == (lst-fst+1));
		cout << (ans ? "Yes" : "No") << endl;
	}
	return 0;
}
