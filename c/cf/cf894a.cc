#include <iostream>
/* CodeForces CF894A problem */
using namespace std;

int main(int argc, char **argv) {
	string s;
	cin >> s;
	int64_t cnt = 0;
	for (int i=0; i<int(s.size())-2; i++)
		for (int j=i+1; j<int(s.size())-1; j++)
			for (int k=j+1; k<int(s.size()); k++)
				if (s[i] == 'Q' && s[j] == 'A' && s[k] == 'Q')
					cnt++;
	cout << cnt << endl;
	return 0;
}
