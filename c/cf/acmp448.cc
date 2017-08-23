/* ACMP 448 */
#include <vector>
#include <cstdio>

//
// prime[i+j] table:
//     1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20
//  1  *  *     *     *           *     *           *     *       
//  2  *     *     *           *     *           *     *          
//  3     *     *           *     *           *     *           * 
//  4  *     *           *     *           *     *           *    
//  5     *           *     *           *     *           *       
//  6  *           *     *           *     *           *          
//  7           *     *           *     *           *             
//  8        *     *           *     *           *                
//  9     *     *           *     *           *                 * 
// 10  *     *           *     *           *                 *    
// 11     *           *     *           *                 *     * 
// 12  *           *     *           *                 *     *    
// 13           *     *           *                 *     *       
// 14        *     *           *                 *     *          
// 15     *     *           *                 *     *             
// 16  *     *           *                 *     *                
// 17     *           *                 *     *                 * 
// 18  *           *                 *     *                 *    
// 19           *                 *     *                 *       
// 20        *                 *     *                 *          
//

using namespace std;

struct isprime {
	vector<bool> p;
	isprime(int sz):p(sz,true) {
		p[0] = p[1] = false;
		for (int i=2; i<sz; i++)
			if (p[i])
				for (int j=i+i; j<sz; j+=i)
					p[j] = false;
	}
	bool operator[](int i) const {
		return p[i];
	}
};

void prn_diag(int n, int beg) {
	for (int i=beg,j=n;i<j;i++,j--)
		printf("%d %d\n", i, j);
}

int main() {
	int n;
	scanf("%d", &n);
	isprime isprime(2*n);
	while (n>1) {
		for (int i=1; i<n; i++) {
			if (isprime[n+i]) {
				prn_diag(n,i);
				n = i-1;
				break;
			}
		}
	}
	return 0;
}
