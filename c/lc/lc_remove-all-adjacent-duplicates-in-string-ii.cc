#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <list>
/* https://leetcode.com/contest/weekly-contest-156/problems/remove-all-adjacent-duplicates-in-string-ii/ */
using namespace std;

class Solution {
	using L = list<pair<char,int>>;
	using LIT = L::iterator;
	static vector<LIT> do_rm(L &str, const vector<LIT> &pos, int k) {
		vector<LIT> res;
		for (auto it:pos) {
			if (it->second % k == 0) {
				LIT pit = prev(it);
				LIT nit = next(it);
				str.erase(it);
				if (nit != str.end() && nit->second < k && pit->first == nit->first) {
					// merge
					pit->second += nit->second;
					str.erase(nit);
					if (pit->second >= k)
						res.push_back(pit);
				}
			} else {
				it->second %= k;
				LIT pit = prev(it);
				if (pit->first == it->first) {
					// merge
					pit->second += it->second;
					str.erase(it);
					if (pit->second >= k)
						res.push_back(pit);
				}
			}
		}
		return res;
	}
public:
    static string removeDuplicates(const string &s, int k) {
        L str;
		vector<LIT> sit;
		char pc = s[0];
		int cnt = 1;
		str.push_back(make_pair(-1,0));
		for (int i=1; i<s.size(); i++) {
			if (s[i] == pc) {
				cnt++;
			} else {
				str.push_back(make_pair(pc, cnt));
				if (cnt >= k)
					sit.push_back(prev(str.end()));
				pc = s[i];
				cnt = 1;
			}
		}
		str.push_back(make_pair(pc, cnt));
		if (cnt >= k)
			sit.push_back(prev(str.end()));
		do {
			sit = do_rm(str, sit, k);
		} while (sit.size() > 0);
		string ans;
		for (auto it:str)
			for (int i=0; i<it.second; i++)
				ans.push_back(it.first);
		return ans;
    }
};

int main(int argc, char **argv) {
    cout << Solution::removeDuplicates("abcd", 2) << endl;
    cout << Solution::removeDuplicates("deeedbbcccbdaa", 3) << endl;
    cout << Solution::removeDuplicates("pbbcggttciiippooaais", 2) << endl;
    cout << Solution::removeDuplicates("wilddddddddddgooowwwwwwwwwwoooossssssssssoccccccchhhhhhhhhhcccccccccccccooryyyyyyyffffffffffyyynaicv", 10) << endl;
    return 0;
}
