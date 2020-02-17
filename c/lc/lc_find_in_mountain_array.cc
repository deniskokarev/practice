#include <iostream>
#include <vector>
/* https://leetcode.com/problems/find-in-mountain-array */
using namespace std;

struct MountainArray {
	vector<int> vv;
	int get(int index) const {
		return vv[index];
	}
	int length() const {
		return vv.size();
	}
};

static int enableFastIO() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	return 0;
}

static const int fastIO = enableFastIO();

class Solution {
public:
	static int findInMountainArray(int target, const MountainArray &mountainArr) {
		// find max
		int f=0, t=mountainArr.length();
		int d3 = (t-f)/3;
		while (d3 > 0) {
			int m1 = f+d3;
			int m2 = t-d3;
			if (mountainArr.get(m1) < mountainArr.get(m2))
				f = m1;
			else
				t = m2;
			d3 = (t-f)/3;
		}
		int mxi;
		if (mountainArr.get(f) < mountainArr.get(t-1))
			mxi = t-1;
		else
			mxi = f;
		//cerr << "mxi=" << mxi << endl;
		// find target to the left
		f = 0, t = mxi+1;
		while (f<t) {
			int m = f+(t-f)/2;
			if (mountainArr.get(m) < target)
				f = m+1;
			else
				t = m;
		}
		if (mountainArr.get(f) == target)
			return f;
		// find target to the right
		f = mxi, t = mountainArr.length();
		while (f<t) {
			int m = f+(t-f)/2;
			if (mountainArr.get(m) > target)
				f = m+1;
			else
				t = m;
		}
		if (f<mountainArr.length() && mountainArr.get(f) == target)
			return f;
		return -1;
	}
};

int main(int argc, char **argv) {
	cout << Solution::findInMountainArray(2, MountainArray {{1,2}}) << '\n';
	cout << Solution::findInMountainArray(3, MountainArray {{1,2,3,4,5,3,1}}) << '\n';
	cout << Solution::findInMountainArray(3, MountainArray {{0,1,2,4,2,1}}) << '\n';
	cout << Solution::findInMountainArray(0, MountainArray {{1,2,5}}) << '\n';
	cout << Solution::findInMountainArray(1, MountainArray {{1,2,5}}) << '\n';
	cout << Solution::findInMountainArray(2, MountainArray {{1,2,5}}) << '\n';
	cout << Solution::findInMountainArray(5, MountainArray {{1,2,5}}) << '\n';
	cout << Solution::findInMountainArray(0, MountainArray {{1,5,2}}) << '\n';
	return 0;
}
