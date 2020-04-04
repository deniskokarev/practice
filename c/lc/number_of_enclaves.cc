#include <iostream>
#include <vector>
/* https://leetcode.com/problems/number-of-enclaves */
using namespace std;

int dsu_root(int a, vector<int> &parent) {
	return (a == parent[a]) ? a : parent[a] = dsu_root(parent[a], parent);
}

void dsu_join(int a, int b, vector<int> &parent) {
	parent[dsu_root(b, parent)] = dsu_root(a, parent);
}

static struct P {
	int x, y;
} mvlst[] {{1,0},{0,1}};

class Solution {
	static int node_num(int x, int y, int szx) {
		return y*szx + x;
	}
public:
    static int numEnclaves(vector<vector<int>>& A) {
		int szy = A.size();
		int szx = A[0].size();
		vector<vector<int>> mm(szy+2, vector<int>(szx+2));
		vector<int> parent((szx+2)*(szy+2));
		for (int y=0; y<szy+2; y++)
			mm[y][0] = mm[y][szx+1] = 1;
		for (int x=0; x<szx+2; x++)
			mm[0][x] = mm[szy+1][x] = 1;
		for (int y=0; y<szy; y++) {
			for (int x=0; x<szx; x++) {
				mm[y+1][x+1] = A[y][x];
				if (mm[y+1][x+1])
					parent[node_num(x+1, y+1, szx+2)] = node_num(x+1, y+1, szx+2);
			}
		}
		for (int y=0; y<=szy; y++)
			for (int x=0; x<=szx; x++)
				if (mm[y][x])
					for (auto m:mvlst)
						if (mm[y+m.y][x+m.x])
							dsu_join(node_num(x+m.x, y+m.y, szx+2), node_num(x, y, szx+2), parent);
		int ans = 0;
		for (int y=0; y<=szy+1; y++)
			for (int x=0; x<=szx+1; x++)
				if (mm[y][x])
					ans += (dsu_root(node_num(x, y, szx+2), parent) != dsu_root(0, parent));
		return ans;
    }
};

void test1() {
	vector<vector<int>> A {{0,0,0,0},{1,0,1,0},{0,1,1,0},{0,0,0,0}};
	cerr << Solution::numEnclaves(A) << endl;;
}

void test2() {
	vector<vector<int>> A {{0,1,1,0},{0,0,1,0},{0,0,1,0},{0,0,0,0}};
	cerr << Solution::numEnclaves(A) << endl;;
}

void test3() {
	vector<vector<int>> A {
		{0,0,0,1,1,1,0,1,0,0},
		{1,1,0,0,0,1,0,1,1,1},
		{0,0,0,1,1,1,0,1,0,0},
		{0,1,1,0,0,0,1,0,1,0},
		{0,1,1,1,1,1,0,0,1,0},
		{0,0,1,0,1,1,1,1,0,1},
		{0,1,1,0,0,0,1,1,1,1},
		{0,0,1,0,0,1,0,1,0,1},
		{1,0,1,0,1,1,0,0,0,0},
		{0,0,0,0,1,1,0,0,0,1}
	};
	cerr << Solution::numEnclaves(A) << endl;;	
}

int main(int argc, char **argv) {
	test1();
	test2();
	test3();
	return 0;
}
