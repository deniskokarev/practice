#include <cstdio>
#include <cstring>
#include <unordered_map>
/* Hackerrank https://www.hackerrank.com/challenges/frequency-queries */

constexpr int MXQ = 1e6+3;

int main(int argc, char **argv) {
	int q;
	scanf("%d", &q);
	std::unordered_map<int,int> cnt(MXQ);
	std::unordered_map<int,int> freq(MXQ);
	while (q--) {
		int qt, v;
		scanf("%d%d", &qt, &v);
		int of;
		switch (qt) {
		case 1:
			of = cnt[v];
			if (of)
				freq[of]--;
			cnt[v]++;
			freq[of+1]++;
			break;
		case 2:
			of = cnt[v];
			if (of) {
				freq[of]--;
				cnt[v]--;
				if (of > 1)
					freq[of-1]++;
			}
			break;
		default:
			if (freq[v])
				printf("1\n");
			else
				printf("0\n");
		}
	}
	return 0;
}
