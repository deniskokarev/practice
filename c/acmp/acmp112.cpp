/* ACMP 112 */
#include <stdio.h>

// merge sort and count the number of swaps over greater elements
int merge_stage(int *a, int asz, int *b, int bsz, int *c) {
	int cnt = 0;
	while (asz > 0 && bsz > 0) {
		while (bsz > 0 && *a > *b) {
			*c++ = *b++;
			bsz--;
			cnt += asz;
		}
		while (asz > 0 && *b >= *a) {
			*c++ = *a++;
			asz--;
		}
	}
	while (asz--)
		*c++ = *a++;
	while (bsz--)
		*c++ = *b++;
	return cnt;
}

// mergesort and count the number of swaps over greater elements
int merge_sort(int *mfrom, int *mto, int n) {
	int cnt = 0;
	for (int msz=1; msz<n; msz *= 2) {
		for (int i=0; i<n; i+=2*msz) {
			if (i+2*msz < n)
				cnt += merge_stage(mfrom+i, msz, mfrom+i+msz, msz, mto+i);
			else if (i+msz < n)
				cnt += merge_stage(mfrom+i, msz, mfrom+i+msz, n-i-msz, mto+i);
			else
				cnt += merge_stage(mfrom+i, n-i, nullptr, 0, mto+i);
		}
		int *tmp = mfrom;
		mfrom = mto;
		mto = tmp;
	}
	return cnt;
}

int main(int argc, char **argv) {
	int n, k;
	scanf("%d%d", &n, &k);
	int ans = 0;
	while (k--) {
		int buf[2][n];
		int *mfrom = buf[0], *mto = buf[1];
		for (auto &a:buf[0])
			scanf("%d", &a);
		ans += merge_sort(mfrom, mto, n);
	}
	printf("%d\n", ans);
	return 0;
}
