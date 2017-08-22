/* ACMP 384 */
#include <iostream>
 
/**
 * GCD(a, b) - greatest common divisor
 */
uint64_t gcd(uint64_t a, uint64_t b) {
    while (b > 0) {
        uint64_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
 
using namespace std;
 
uint64_t mod = 1e9;
 
int main() {
    int i, j;
    cin >> i >> j;
    int mn = min(i, j);
    j = max(i, j);
    i = mn;
    uint64_t f1, f2;
    f1=0; f2=1;
    for (;i>0;--i,--j) {
        uint64_t f = f1+f2;
        f1 = f2;
        f2 = f%mod;
    }
    uint64_t n1 = f1;
    for (;j>0;--j) {
        uint64_t f = f1+f2;
        f1 = f2;
        f2 = f%n1;
    }
    uint64_t n2 = f1;
    cout << gcd(n2+n1,n1)%n1 << endl;
}
