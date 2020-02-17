#include <iostream>
#include <vector>
#include <algorithm>
/* https://leetcode.com/problems/video-stitching/ */
using namespace std;

constexpr int INF = 1e6;

class Solution {
public:
    static int videoStitching(vector<vector<int>> &clips, int T) {
		sort(clips.begin(), clips.end(), [](const vector<int> &a, const vector<int> &b){return a[0]<b[0];});
		vector<vector<int>> sol(T+1, vector<int>(clips.size()+1, INF));
		for (int i=0; i<=clips.size(); i++)
			sol[0][i] = 0;
		for (int t=1; t<=T; t++) {
			for (int i=0; i<clips.size(); i++) {
				sol[t][i+1] = min(sol[t][i+1], sol[t][i]);
				if (clips[i][0] <= t && t <= clips[i][1]) {
					for (int x = clips[i][0]; x<=t; x++)
						sol[t][i+1] = min(sol[t][i+1], sol[x][i]+1);
				}
			}
		}
		int ans = sol[T][clips.size()];
        return ans < INF ? ans : -1;
    }
};

void test1() {
	vector<vector<int>> clips = {{0,2},{4,6},{8,10},{1,9},{1,5},{5,9}};
	int T = 10;
	cout << Solution::videoStitching(clips, T) << endl;
}
void test2() {
	vector<vector<int>> clips = {{0,1},{1,2}};
	int T = 5;
	cout << Solution::videoStitching(clips, T) << endl;
}
void test3() {
	vector<vector<int>> clips = {{0,1},{6,8},{0,2},{5,6},{0,4},{0,3},{6,7},{1,3},{4,7},{1,4},{2,5},{2,6},{3,4},{4,5},{5,7},{6,9}};
	int T = 9;
	cout << Solution::videoStitching(clips, T) << endl;
}

int main() {
	test1();
	test2();
	test3();
	return 0;
}
