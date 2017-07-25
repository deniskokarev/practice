#include <iostream>
/* CodeForces CF821B problem */
using namespace std;

int main(int argc, char **argv) {
	int64_t m, b;
	cin >> m >> b;
	int64_t mx_v = -1;
	for (int64_t x=0,y=b-(x+m-1)/m; y>=0; x++,y=b-(x+m-1)/m) {
		int64_t v = x*(x+1)/2*(y+1) + y*(y+1)/2*(x+1);
		if (v > mx_v) {
			mx_v = v;
			//cerr << x << ":" << y << " = " << v << endl;
		}
	}
	cout << mx_v << endl;
	return 0;
}
