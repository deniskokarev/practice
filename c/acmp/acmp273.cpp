/* ACMP 273 */
#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

int main(int argc, char **argv) {
	string sn;
	cin >> sn;
	for (auto &c:sn)
		c -= '0';
	int nn[1000];
	fill(nn, nn+1000, 0);
	for (int i=0; i<sn.length()-2; i++)
		for (int j=i+1; j<sn.length()-1; j++)
			for(int k=j+1; k<sn.length(); k++)
				nn[sn[i]*100+sn[j]*10+sn[k]] = 1;
	uint64_t s = accumulate(nn+100, nn+1000, 0ULL);
	cout << s << endl;
	return 0;
}
