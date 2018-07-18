#include <cstdio>
#include <cstring>
#include <cassert>
/* ACMP 458 */
using namespace std;

int main(int argc, char **argv) {
	int h;
	scanf("%d", &h);
	int oo[h];
	for (auto &o:oo)
		scanf("%d", &o);
	int rr[h];
	for (int i=0; i<h; i++)
		rr[oo[i]-1] = i;
	char s[1024];
	memset(s, ' ', sizeof(s));
	scanf(" %1023s", s);
	int sln = strlen(s);
	int w = (sln+h-1)/h;
	for (int c=0; c<w; c++)
		for (int r=0; r<h; r++)
			fputc(s[w*rr[r]+c], stdout);
	fputc('\n', stdout);
	return 0;
}
