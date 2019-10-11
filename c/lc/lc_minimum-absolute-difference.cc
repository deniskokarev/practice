#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
/* https://leetcode.com/contest/weekly-contest-155/problems/minimum-absolute-difference/ */
using namespace std;

class Solution {
public:
    vector<vector<int>> minimumAbsDifference(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        int mn = INT_MAX;
        for (int i=1; i<arr.size(); i++)
            mn = min(mn, arr[i]-arr[i-1]);
        vector<vector<int>> res;
        for (int i=1; i<arr.size(); i++) {
            if (arr[i]-arr[i-1] == mn) {
                res.push_back(vector<int>{arr[i-1], arr[i]});
            }
        }
        return res;
    }
};

int main(int argc, char **argv) {
	cout << "real answer" << endl;
	return 0;
}
