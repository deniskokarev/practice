// https://leetcode.com/problems/string-matching-in-an-array
// bruteforce
class Solution {
public:
	vector<string> stringMatching(const vector<string>& words) {
		int sz = words.size();
		set<string> res;
		for (int i = 0; i < sz; i++)
		{
			for (int j = 0; j < sz; j++)
			{
				if (i != j)
				{
					if (words[i].find(words[j]) != string::npos)
					{
						res.insert(words[j]);
					}
				}
			}
		}
		return {res.begin(), res.end()};
	}
};
