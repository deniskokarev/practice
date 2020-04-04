#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
/* https://leetcode.com/contest/weekly-contest-155/problems/smallest-string-with-swaps/ */
using namespace std;

class Solution {
	/*
	 * disjoint set ops
	 */
	static int dsu_root(int a, vector<int> &parent) {
		return (a == parent[a]) ? a : parent[a] = dsu_root(parent[a], parent);
	}
	static void dsu_join(int a, int b, vector<int> &parent) {
		parent[dsu_root(b, parent)] = dsu_root(a, parent);
	}
public:
	static string smallestStringWithSwaps(string s, const vector<vector<int>>& pairs) {
		vector<int> parent(s.size());
		for (int i=0; i<parent.size(); i++)
			parent[i] = i;
		for (auto p:pairs)
			dsu_join(p[0], p[1], parent);
		vector<string> ss(s.size());
		for (int i=0; i<s.size(); i++)
			ss[dsu_root(i, parent)] += s[i];
		for (int i=0; i<s.size(); i++)
			sort(ss[i].begin(), ss[i].end());
		string res(s);
		for (int i=s.size()-1; i>=0; i--) {
			res[i] = ss[dsu_root(i, parent)].back();
			ss[dsu_root(i, parent)].pop_back();
		}
		return res;
	}
};

int main(int argc, char **argv) {
	cout << Solution::smallestStringWithSwaps("dcab", {{0,3},{1,2}}) << endl;
	cout << Solution::smallestStringWithSwaps("dcab", {{0,3},{1,2},{0,2}}) << endl;
	return 0;
}
