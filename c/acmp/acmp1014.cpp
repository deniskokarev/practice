/* ACMP 1014 */
#include <iostream>
#include <vector>

using namespace std;

constexpr uint64_t mod = 1e9+9;

/*
 * Short answer is "deranegemts" 
 *
 * Need to consider Hamilton path in entire graph, plus the combination of a ham path without
 * 2 nodes, plus the combination of the ham path in 3 node graph and the rest of the graph
 * without those 3 nodes, etc
 *
 * Recurrent solution:
 * f(n)
 *      | (n < 2) = 0 
 *      | otherwise = (n-1)! + sum(i=[1,n-3], choose(n-1, i)*f(n-i-1)*i!)
 *
 * Which may be folded into
 *
 * f(n) = (n-1)! + (n-1) * (f(n-2) + f(n-1) - (n-2)!)
 *
 * Yes, you can consider the list as a combination of Hamiltonian paths,
 * but at the end, it gets to the number of derangements (all elements palced in wrong spot)
 *
 * f(n) = (n-1)! + (n-1) * (f(n-2) + f(n-1) - (n-2)!)
 * f(n) = (n-1) * (n-2)! + (n-1) * (f(n-2) + f(n-1) - (n-2)!)
 * f(n) = (n-1) * ((n-2)! + f(n-2) + f(n-1) - (n-2)!)
 * f(n) = (n-1) * (f(n-2) + f(n-1))
 * ^^^^
 * this is a recursive formula for derangements: !n
 *
 */
int main(int argc, char **argv) {
	int cnt;
	cin >> cnt;
	uint64_t n1 = 1; // !(n-1)
	uint64_t n2 = 0; // !(n-2)
	uint64_t n;
	for (unsigned i=3; i<cnt+2; i++) {
		n = (n1 + n2) * (i-1);
		n %= mod;
		n2 = n1;
		n1 = n;
	}
	cout << n2 << endl;
	return 0;
}
