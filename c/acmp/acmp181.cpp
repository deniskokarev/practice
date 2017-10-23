/* ACMP 181 */
#include <unordered_map>
#include <cstdio>

using namespace std;

static const unordered_map<char,int> cmd{{'N', 0}, {'S', 1}, {'W', 2}, {'E', 3}, {'U', 4}, {'D', 5}};

#define dim(A) (sizeof(A)/sizeof(A[0]))

int main(int argc, char **argv) {
	int pp[6][101];
	for (int pi=0; pi<dim(pp); pi++) {
		int *p = pp[pi];
		p[0] = 0;
		for (int c; (c=fgetc(stdin)) != '\n' && p[0]<101; p[0]++)
			p[1+p[0]] = cmd.at(c);
	}
	char bc;
	int n;
	fscanf(stdin, "%c%d", &bc, &n);
	int b = cmd.at(bc);
	uint64_t cc[2][6];
	fill(cc[0], cc[0]+dim(cc[0]), 0);
	for (int i=1; i<=n; i++) {
		int curr = i&1;
		int prev = (i+1)&1;
		fill(cc[curr], cc[curr]+dim(cc[0]), 1); // 1
		for (int j=0; j<dim(cc[0]); j++)
			for (int k=1; k<=pp[j][0]; k++)
				cc[curr][j] += cc[prev][pp[j][k]];
	}
	fprintf(stdout, "%lld\n", cc[n&1][b]);
	return 0;
}
