#include <iostream>
#include <vector>
/* https://leetcode.com/contest/weekly-contest-132/problems/divisor-game/ */
using namespace std;


class Solution {
public:
    static bool divisorGame(int N) {
		vector<int> sol(N+1);
		sol[0] = sol[1] = -1;
		int player = 1;
		for (int i=2; i<=N; i++) {
			sol[i] = -player;
			for (int f=1; f<i; f++) {
				if (i%f == 0 && sol[i-f] == -player) {
					sol[i] = player;
					break;
				}
			}
			player *= -1;
		}
#if 0
		for (int i=0; i<=N; i++)
			cerr << sol[i] << ' ';
		cerr << "\n";
#endif
		return (sol[N] == 1);
    }
};

void test1() {
	cout << Solution::divisorGame(2) << endl;
}

void test2() {
	cout << Solution::divisorGame(3) << endl;
}

void test3() {
	cout << Solution::divisorGame(13) << endl;
}

void test4() {
	cout << Solution::divisorGame(64) << endl;
}

int main(int argc, char **argv) {
	test1();
	test2();
	test3();
	test4();
	return 0;
}
