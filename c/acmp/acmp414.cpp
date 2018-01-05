/* ACMP 414 */
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int a, b;
	cin >> a >> b;
	int mm[n+1];
	mm[0] = -1;
	mm[1] = 0;
	for (int i=2; i<=n; i++)
		cin >> mm[i];
	int la = 0;
	for (int v=a; v>0; v=mm[v],la++);
	int lb = 0;
	for (int v=b; v>0; v=mm[v],lb++);
	for (; la>lb; a=mm[a],la--);
	for (; lb>la; b=mm[b],lb--);
	for (; a!=b; a=mm[a],b=mm[b]);
	cout << a << endl;
	return 0;
}
