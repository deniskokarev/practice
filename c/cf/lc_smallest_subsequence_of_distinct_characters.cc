#include <iostream>
#include <vector>
/* https://leetcode.com/problems/smallest-subsequence-of-distinct-characters/ */

using namespace std;

class Solution {
public:
	static string smallestSubsequence(const string &text) {
		vector<int> cnt(256);
		for (auto c:text)
			cnt[c]++;
		int h = 0;
		string res;
		for (int i=0; i<26; i++) {
			for (char c='a'; c<='z'; c++) {
				if (cnt[c] > 0) {
					vector<int> c2(cnt);
					for (int p=h; p<text.size(); p++) {
						if (text[p] == c) {
							res += c;
							c2[c] = 0;
							h = p+1;
							cnt = move(c2);
							goto another_let;
						} else {
							c2[text[p]]--;
							if (c2[text[p]] == 0)
								break;
						}
					}
				}
			}
		another_let:
			;
		}
		return res;
	}
};

int main(int argc, char **argv) {
	cout << Solution::smallestSubsequence("cdadabcc") << endl;
	cout << Solution::smallestSubsequence("abcd") << endl;
	cout << Solution::smallestSubsequence("ecbacba") << endl;
	cout << Solution::smallestSubsequence("leetcode") << endl;
	return 0;
}
