#include <iostream>
#include <vector>
/* https://leetcode.com/contest/weekly-contest-143/problems/distribute-candies-to-people/ */
using namespace std;

class Solution {
public:
	static vector<int> distributeCandies(int candies, int num_people) {
		vector<int> res(num_people);
		int c = 1;
		int i = 0;
		while (candies >= c) {
			res[i % num_people] += c;
			candies -= c;
			c++;
			i++;
		}
		res[i % num_people] += candies;	
		return res;
	}
};

int main(int argc, char **argv) {
	for (auto r:Solution::distributeCandies(1e9, 1000))
		cerr << r << ' ';
	cerr << '\n';
	return 0;
}
