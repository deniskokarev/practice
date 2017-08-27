/* ACMP 448 */
#include <iostream>
#include <vector>
 
// основаня идея решения базируется на вот такой табличке
// где * означает простую сумму i+j
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
 
void prn_diagonal(int n, int beg) {
	for (int i=beg,j=n;i<j;i++,j--)
		cout << i << ' ' << j << '\n';
	// cout << i << ' ' << j << endl; // так слишком медленно
}
 
int main() {
	ios_base::sync_with_stdio(false); // иначе слишком медленно
	int n;
	cin >> n;
	isprime isprime(2*n);
	while (n>1) {
		for (int i=1; i<n; i++) {
			if (isprime[n+i]) {
				prn_diagonal(n,i);
				n = i-1;
				break;
			}
		}
	}
	return 0;
}
