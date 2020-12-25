// https://www.hackerrank.com/challenges/maximum-xor/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=miscellaneous
#include <cstdio>
#include <vector>
#include <array>
#include <bitset>

using namespace std;

enum {L, R};

struct N {
	array<int,2> chld;
};

void trie_insert(vector<N> &trie, const bitset<31> &bits) {
	int root = 1;
	for (int b=30; b>=0; b--) {
		if (!trie[root].chld[bits[b]]) {
			trie.push_back({{0}});
			trie[root].chld[bits[b]] = trie.size()-1;
		}
		root = trie[root].chld[bits[b]];
	}
}

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	vector<N> trie(2);
	trie[1] = {{0}};
	while (n--) {
		int a;
		scanf("%d", &a);
		trie_insert(trie, bitset<31>(a));
	}
	int q;
	scanf("%d", &q);
	while (q--) {
		int x;
		scanf("%d", &x);
		int root = 1, add = 0, val = 0;
		for (int b=(1<<30); b>0; b/=2) {
			if (x&b) {
				if (trie[root].chld[L]) {
					add += b;
					root = trie[root].chld[L];
				} else {
					add -= b;
					root = trie[root].chld[R];
					val += b;
				}
			} else {
				if (trie[root].chld[R]) {
					root = trie[root].chld[R];
					val += b;
				} else {
					root = trie[root].chld[L];
				}
			}
		}
		printf("%d\n", val+add);
	}
	return 0;
}

