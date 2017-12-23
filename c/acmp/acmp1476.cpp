/* ACMP 1476 */
#include <stdio.h>
#include <memory.h>

constexpr int MXSZ = 1e5 + 18; // + ~log2(1e5)
constexpr int len = 316; // ~ sqrt(MXSZ);

int main(int argc, char **argv) {
	unsigned char bb[MXSZ];
	int bucket[(MXSZ+len-1)/len];	// has number of 1s
	memset(bucket, 0, sizeof(bucket));
	int n;
	scanf("%d", &n);
	while (n-- > 0) {
		char op[32];
		int s;
		scanf("%31s %d", op, &s);
		int b = s/len;
		int i;
		if (bucket[b] == 0)
			memset(bb+b*len, 0, sizeof(bb[0])*len);
		else if (bucket[b] == len)
			memset(bb+b*len, 1, sizeof(bb[0])*len);	
		switch(op[0]) {
		case 'a':
			for (i=s; bb[i] == 1 && i<(b+1)*len; i++) {
				bb[i] = 0;
				bucket[b]--;
			}
			if (i == (b+1)*len) {
				for (b++; bucket[b] == len; b++)
					bucket[b] = 0;
				for (i=b*len; bb[i] == 1; i++) {
					bb[i] = 0;
					bucket[b]--;
				}
			}
			bb[i] = 1;
			bucket[b]++;
			break;
		case 's':
			for (i=s; bb[i] == 0 && i<(b+1)*len; i++) {
				bb[i] = 1;
				bucket[b]++;
			}
			if (i == (b+1)*len) {
				for (b++; bucket[b] == 0; b++)
					bucket[b] = len;
				for (i=b*len; bb[i] == 0; i++) {
					bb[i] = 1;
					bucket[b]++;
				}
			}
			bb[i] = 0;
			bucket[b]--;
			break;
		}
		int sum = 0;
		for (auto &b:bucket)
			sum += b;
		printf("%d\n", sum);
	}
	return 0;
}
