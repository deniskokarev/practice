#include <iostream>
#include <vector>
/* https://leetcode.com/problems/peak-index-in-a-mountain-array */
using namespace std;

class Solution {
public:
    static inline int peakIndexInMountainArray(const vector<int> &arr) {
        int sz = arr.size();
        int f = 1, t = sz;
        while (f < t) {
            int m = (f + t) / 2;
            if (arr[m - 1] < arr[m]) {
                f = m + 1;
            } else {
                t = m;
            }
        }
        return f - 1;
    }
};


class Solution {
public:
	static int peakIndexInMountainArray(const vector<int>& A) {
		int f=1, t=A.size()-2;
		while (f < t) {
			int m = f+(t-f)/2;
			if (A[m] < A[m+1])
				f = m+1;
			else
				t = m;
		}
		return f;
	}
};

int main(int argc, char **argv) {
	cout << Solution::peakIndexInMountainArray({0,1,0}) << endl;
	cout << Solution::peakIndexInMountainArray({0,2,1,0}) << endl;
	cout << Solution::peakIndexInMountainArray({0,1,2,1,0}) << endl;
	cout << Solution::peakIndexInMountainArray({0,1,2,0}) << endl;
}
