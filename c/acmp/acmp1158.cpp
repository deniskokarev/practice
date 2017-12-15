/* ACMP 1158 */
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>

struct SA_SP {
	unsigned pos;
	unsigned score[2]; // score for two halfs and remainder
};

#define dim(X)	(sizeof(X)/sizeof(X[0]))
				 
static int cmp_score(const void *a, const void *b) {
	SA_SP *pa = (SA_SP*)a;
	SA_SP *pb = (SA_SP*)b;
	int d;
	int i = 0;
	do {
		d = (int)pa->score[i] - (int)pb->score[i];
		i++;
	} while(d==0 && i<dim(pa->score));
	return d;
}

static void one_sort_stage(SA_SP *sp, SA_SP *tmp, const char *s, unsigned sz, unsigned len) {
	unsigned hlen = len>>1;
	for (unsigned i=0; i<sz; i++) {
		tmp[i].score[0] = sp[i].score[0];
		tmp[i].score[1] = sp[i+hlen].score[0]*256 + s[i+len-1];
		tmp[i].pos = i;
	}
	qsort(tmp, sz, sizeof(tmp[0]), cmp_score);
	unsigned ns = 0;
	unsigned *os = tmp[0].score;
	for (unsigned i=0; i<sz; i++) {
		if (memcmp(os, tmp[i].score, sizeof(tmp[i].score)) != 0) {
			os = tmp[i].score;
			ns++;
		}
		int p = tmp[i].pos;
		sp[p].score[0] = ns;
	}
	memcpy(sp+sz, sp, sz*(sizeof(sp[0])));
}

// build suffix array for the string s
// simple O(N*log(N)*log(N)) solution
// s content must be duplicated (sz is still the size of the original str)
// sa temporary buffer must have 4*sz free space
// dst result must have sz free space
void suffix_array(unsigned *dst, const char *s, unsigned sz, SA_SP *sa) {
	unsigned len_stages[32];
	unsigned n, p2 = 0;
	for (p2=0,n=sz; n>0; n>>=1,p2++)
		len_stages[p2] = n;
	SA_SP *sp = sa;
	SA_SP *tmp = sa+sz*2;
	memset(sp, 0, sizeof(sp[0])*sz*2);
	for (int i=0; i<sz; i++)
		sp[i].pos = sp[i+sz].pos = i;
	for (int i=p2-1; i>=0; i--)
		one_sort_stage(sp, tmp, s, sz, len_stages[i]);
	for (int i=0; i<sz; i++)
		dst[i] = tmp[i].pos;
}
  
int main(int argc, char **argv) {
	char ss[200001];
	int rc = scanf("%100000s", ss);
	unsigned len = (unsigned)strlen(ss);
	assert(rc == 1 && len <= 100000 && "problem with input data constraints");
	memcpy(ss+len, ss, sizeof(ss[0])*len);
	SA_SP sp[len*4];
	unsigned pos[len];
	suffix_array(pos, ss, len, sp);
	int fp = -1;
	char out[len];
	for (int i=0; i<len; i++) {
		if (pos[i] == 0)
			fp = i;
#if 0
		// debug print sorted suffixes
		for (int j=0; j<len; j++)
			fputc(ss[pos[i]+j], stderr);
		fputc('\n', stderr);
#endif
		out[i] = ss[pos[i]+len-1];
	}
	fprintf(stdout, "%d\n", fp+1);
	fwrite(out, 1, len, stdout);
	fputc('\n', stdout);
	return 0;
}
