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
	char si[1024];
	scanf(" %1023s", si);
	int sln = strlen(si);
	int w = (sln+h-1)/h;
	int rem = h*w-sln;
	char so[h][w];
	memset(so, ' ', sizeof(so));
	int p = 0, rln;
	for (int r=0; r<h; r++) {
		if (oo[r] > h-rem)
			rln = w-1;
		else
			rln = w;
		memcpy(so[oo[r]-1], si+p, rln);
		p += rln;
	}
	for (int c=0; c<w; c++)
		for (int r=0; r<h; r++)
			fputc(so[r][c], stdout);
	fputc('\n', stdout);
	return 0;
}
