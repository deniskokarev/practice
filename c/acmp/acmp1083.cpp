/* ACMP 1083 */
#include <cstdio>
#include <cstring>
#include <climits>
#include <cassert>

#define min(A,B) ((A<B)?A:B)
#define dim(X)	((int)(sizeof(X)/sizeof(X[0])))

typedef struct {
	long long sum;
	int set;
	int inc;
	int min;
} BUCKET;
		
static void scatter_bucket(int *aa, int len, BUCKET *bucket, int b) {
	if (bucket[b].set >= 0) {
		for (int i=b*len; i<(b+1)*len; i++)
			aa[i] = bucket[b].set;
		bucket[b].set = -1;
	}
	for (int i=b*len; i<(b+1)*len; i++)
		aa[i] += bucket[b].inc;
	bucket[b].inc = 0;
}

BUCKET bucket[15];
constexpr int len = 3001;
int aa[len*dim(bucket)];

int main(int argc, char **argv) {
	int rc;
	int n;
	rc = scanf("%d", &n);
	assert(rc == 1 && "expected input format");
	assert(n<dim(aa) && "must not exceed buffer size");
	for (auto &b:bucket) {
		b.sum = 0;
		b.set = -1;
		b.inc = 0;
		b.min = INT_MAX;
	}
	for (int i=0; i<n; i++) {
		rc = scanf("%d", &aa[i]);
		assert(rc == 1 && "expected input format");
		int b = i/len;
		bucket[b].min = min(bucket[b].min, aa[i]);
		bucket[b].sum += aa[i];
	}
	int m;
	rc = scanf("%d", &m);
	assert(rc == 1 && "expected input format");
	while (m-- > 0) {
		char op[32];
		int b, i, l, r, x;
		rc = scanf("%s", op);
		assert(rc == 1 && "expected input format");
		if (strcmp(op, "get") == 0) {
			rc = scanf("%d", &i);
			assert(rc == 1 && "expected input format");
			i--;
			b = i/len;
			printf("%d\n", ((bucket[b].set>=0)?bucket[b].set:aa[i])+bucket[b].inc);
		} else if (strcmp(op, "update") == 0) {
			rc = scanf("%d%d%d", &l, &r, &x);
			assert(rc == 3 && "expected input format");
			l--, r--;
			for (b=l/len+1; b<r/len; b++) {
				bucket[b].sum = x*len;
				bucket[b].set = x;
				bucket[b].inc = 0;
				bucket[b].min = x;
			}
			if (l/len < r/len) {
				b = l/len;
				scatter_bucket(aa, len, bucket, b);
				bucket[b].min = min(bucket[b].min, x);
				for (int i=l; i<(b+1)*len; i++) {
					bucket[b].sum -= aa[i];
					aa[i] = x;
					bucket[b].sum += aa[i];
				}
				b = r/len;
				scatter_bucket(aa, len, bucket, b);
				bucket[b].min = min(bucket[b].min, x);
				for (int i=b*len; i<=r; i++) {
					bucket[b].sum -= aa[i];
					aa[i] = x;
					bucket[b].sum += aa[i];
				}				
			} else {
				b = l/len;
				scatter_bucket(aa, len, bucket, b);
				bucket[b].min = min(bucket[b].min, x);
				for (int i=l; i<=r; i++) {
					bucket[b].sum -= aa[i];
					aa[i] = x;
					bucket[b].sum += aa[i];
				}
			}
		} else if (strcmp(op, "add") == 0) {
			rc = scanf("%d%d%d", &l, &r, &x);
			assert(rc == 3 && "expected input format");
			l--, r--;
			for (b=l/len+1; b<r/len; b++) {
				bucket[b].sum += x*len;
				bucket[b].inc += x;
				bucket[b].min += x;
			}
			if (l/len < r/len) {
				b = l/len;
				scatter_bucket(aa, len, bucket, b);
				for (int i=l; i<(b+1)*len; i++) {
					aa[i] += x;
					bucket[b].sum += x;
					bucket[b].min = min(bucket[b].min, aa[i]);
				}
				b = r/len;
				scatter_bucket(aa, len, bucket, b);
				for (int i=b*len; i<=r; i++) {
					aa[i] += x;
					bucket[b].sum += x;
					bucket[b].min = min(bucket[b].min, aa[i]);
				}
			} else {
				b = l/len;
				scatter_bucket(aa, len, bucket, b);
				for (int i=l; i<=r; i++) {
					aa[i] += x;
					bucket[b].sum += x;
					bucket[b].min = min(bucket[b].min, aa[i]);
				}
			}
		} else if (strcmp(op, "rsq") == 0) {
			rc = scanf("%d%d", &l, &r);
			assert(rc == 2 && "expected input format");
			l--, r--;
			long long sum = 0;
			for (b=l/len+1; b<r/len; b++)
				sum += bucket[b].sum;
			if (l/len < r/len) {
				b = l/len;
				for (int i=l; i<(b+1)*len; i++)
					sum += ((bucket[b].set>=0)?bucket[b].set:aa[i]) + bucket[b].inc;
				b = r/len;
				for (int i=b*len; i<=r; i++)
					sum += ((bucket[b].set>=0)?bucket[b].set:aa[i]) + bucket[b].inc;
			} else {
				b = l/len;
				for (int i=l; i<=r; i++)
					sum += ((bucket[b].set>=0)?bucket[b].set:aa[i]) + bucket[b].inc;
			}
			printf("%lld\n", sum);
		} else if (strcmp(op, "rmq") == 0) {
			rc = scanf("%d%d", &l, &r);
			assert(rc == 2 && "expected input format");
			l--, r--;
			int mn = INT_MAX;
			for (b=l/len+1; b<r/len; b++)
				mn = min(mn, bucket[b].min);
			if (l/len < r/len) {
				b = l/len;
				for (int i=l; i<(b+1)*len; i++)
					mn = min(mn, ((bucket[b].set>=0)?bucket[b].set:aa[i]) + bucket[b].inc);
				b = r/len;
				for (int i=b*len; i<=r; i++)
					mn = min(mn, ((bucket[b].set>=0)?bucket[b].set:aa[i]) + bucket[b].inc);
			} else {
				b = l/len;
				for (int i=l; i<=r; i++)
					mn = min(mn, ((bucket[b].set>=0)?bucket[b].set:aa[i]) + bucket[b].inc);
			}
			printf("%d\n", mn);
		}
	}
	return 0;
}
