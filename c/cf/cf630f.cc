#include <iostream>
#include <vector>
#include <cassert>

/*

One company of IT City decided to create a group of innovative developments consisting from 5 to 7 people and hire new employees for it. After placing an advertisment the company received n resumes. Now the HR department has to evaluate each possible group composition and select one of them. Your task is to count the number of variants of group composition to evaluate.
Input

The only line of the input contains one integer n (7 ≤ n ≤ 777) — the number of potential employees that sent resumes.
Output

Output one integer — the number of different variants of group composition.

Examples
Input

7

Output

29

*/

uint64_t choose(uint16_t n, uint16_t k) {
	assert(k <= n);
	uint64_t res = 1;
	for (uint64_t i=n,j=1; j<=k; i--,j++) {
		res *= i;
		res /= j;
	}
	return res;
}

int main(int argc, char **argv) {
	unsigned n;
	std::cin >> n;
	std::cout << choose(n, 5)+choose(n, 6)+choose(n, 7) << std::endl;
}
