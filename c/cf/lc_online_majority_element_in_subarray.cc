#include <iostream>
#include <vector>
/* https://leetcode.com/contest/weekly-contest-149/problems/online-majority-element-in-subarray/ */
using namespace std;

class MajorityChecker {
	static constexpr int BITS = 15;
	static constexpr int MX = (1<<BITS)+1;
	static int fw_sum(const vector<int> &fw, int p) {
		int s = 0;
		for (; p>=0; p=(p&(p+1))-1)
			s += fw[p];
		return s;
	}
	static void fw_inc(vector<int> &fw, int p, int d) {
		int sz = fw.size();
		for (; p<sz; p|=(p+1))
			fw[p] += d;
	}
	vector<vector<int>> fw;
	vector<vector<int>> pos;
public:
	MajorityChecker(const vector<int>& arr):fw(BITS, vector<int>(arr.size())),pos(MX) {
		for (int j=0; j<arr.size(); j++) {
			assert(arr[j]<MX);
			for (int i=0,msk=1; i<BITS; i++,msk*=2)
				fw_inc(fw[i], j, (arr[j]&msk)?1:0);
			pos[arr[j]].push_back(j);
		}
	}
	int query(int left, int right, int threshold) {
		vector<int> bits(BITS);
		for (int i=0; i<BITS; i++)
			bits[i] = fw_sum(fw[i], right)-fw_sum(fw[i], left-1);
		int cand = 0;
		for (int i=BITS-1; i>=0; i--) {
			cand *= 2;
			cand += (bits[i]>=threshold);
		}
		int r = upper_bound(pos[cand].begin(), pos[cand].end(), right) - pos[cand].begin();
		int l = lower_bound(pos[cand].begin(), pos[cand].end(), left) - pos[cand].begin();
		int cand_cnt = r-l;
		if (cand_cnt >= threshold)
			return cand;
		else
			return -1;
	}
};

int main(int argc, char **argv) {
	MajorityChecker mc1({1,1,2,2,1,1});
	cout << mc1.query(0,5,4) << '\n';
	cout << mc1.query(0,3,3) << '\n';
	cout << mc1.query(2,3,2) << '\n';
	MajorityChecker mc2({16,17,18,19,20,21});
	cout << mc2.query(0,5,4) << '\n';
	cout << mc2.query(0,3,3) << '\n';
	cout << mc2.query(2,3,2) << '\n';
	return 0;
}
