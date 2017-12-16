/* ACMP 1158 */
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cstdint>

struct SA_SP {
	unsigned pos;
	uint64_t score; // score for two halfs
};

#define dim(X)	(sizeof(X)/sizeof(X[0]))
				 
static int cmp_score(const void *a, const void *b) {
	SA_SP *pa = (SA_SP*)a;
	SA_SP *pb = (SA_SP*)b;
	return (pa->score > pb->score) - (pa->score < pb->score);
}

static void one_sort_stage(SA_SP *sp, SA_SP *tmp, unsigned sz, unsigned len) {
	for (unsigned i=0; i<sz; i++) {
		tmp[i].score = (sp[i].score << 32) + sp[i+len].score;
		tmp[i].pos = i;
	}
	qsort(tmp, sz, sizeof(tmp[0]), cmp_score);
	unsigned ns = 0;
	uint64_t os = tmp[0].score;
	for (unsigned i=0; i<sz; i++) {
		if (os != tmp[i].score) {
			os = tmp[i].score;
			ns++;
		}
		int p = tmp[i].pos;
		sp[p].score = ns;
	}
	memcpy(sp+sz, sp, sz*(sizeof(sp[0])));
}

// build suffix array for the string s
// simple O(N*log(N)*log(N)) solution
// sa temporary buffer must have 3*sz free space
// dst result must have sz free space
void suffix_array(unsigned *dst, const char *s, unsigned sz, SA_SP *sa) {
	SA_SP *sp = sa;
	SA_SP *tmp = sa+sz*2;
	for (int i=0; i<sz; i++) {
		sp[i].pos = i;
		sp[i].score = s[i];
	}
	memcpy(sp+sz, sp, sz*(sizeof(sp[0])));
	one_sort_stage(sp, tmp, sz, 0);
	for (int p2=1; p2<sz; p2<<=1)
		one_sort_stage(sp, tmp, sz, p2);
	for (int i=0; i<sz; i++)
		dst[i] = tmp[i].pos;
}
  
int main(int argc, char **argv) {
	char ss[100001];
	int rc = scanf("%100000s", ss);
	unsigned len = (unsigned)strlen(ss);
	assert(rc == 1 && len <= 100000 && "problem with input data constraints");
	SA_SP sp[len*3];
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
			fputc(ss[(pos[i]+j)%len], stderr);
		fputc('\n', stderr);
#endif
		out[i] = ss[(pos[i]+len-1)%len];
	}
	fprintf(stdout, "%d\n", fp+1);
	fwrite(out, 1, len, stdout);
	fputc('\n', stdout);
	return 0;
}
