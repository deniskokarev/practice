#include <iostream>
/* https://leetcode.com/problems/smallest-integer-divisible-by-k/ */
using namespace std;

class Solution {
public:
    static int smallestRepunitDivByK(int k) {
		int n = 1;
		int len = 1;
		while (n<k) {
			n *= 10;
			n++;
			len++;
		}
		int rem = n%k;
		while (rem != 0 && len <= k) {
			rem *= 10;
			rem++;
			rem %= k;
			len++;
		}
		return (len <= k) ? len : -1;
    }
};

void test1() {
	cerr << Solution::smallestRepunitDivByK(1) << endl;
}	

void test2() {
	cerr << Solution::smallestRepunitDivByK(2) << endl;
}	

void test3() {
	cerr << Solution::smallestRepunitDivByK(3) << endl;
}

int main(int argc, char **argv) {
	test1();
	test2();
	test3();
	return 0;
}
