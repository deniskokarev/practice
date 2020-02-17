#include <iostream>
/* https://leetcode.com/contest/weekly-contest-130/problems/convert-to-base-2/ */
using namespace std;

class Solution {
public:
    static string baseNeg2(int N) {
        string res;
        int carry = 0;
        int i = 0;
		char sbit[2] = {'0', '1'};
        while (N > 0 || carry > 0) {
            int b = (N & 1) + carry;
			carry = 0;
            if (b>1) {
				b = 0;
                carry = 1;
			}
			if (b>0 && (i&1) == 1)
				carry = 1;
			res += sbit[b];
            i++;
            N /= 2;
        }
		reverse(res.begin(), res.end());
		if (res.size() == 0)
			res = "0";
		return res;
    }
};

void test0() {
	cerr << Solution::baseNeg2(0) << endl;
}

void test1() {
	cerr << Solution::baseNeg2(2) << endl;
}

void test2() {
	cerr << Solution::baseNeg2(3) << endl;
}

void test3() {
	cerr << Solution::baseNeg2(4) << endl;
}

int main(int argc, char **argv) {
	test0();
	test1();
	test2();
	test3();
	return 0;
}
