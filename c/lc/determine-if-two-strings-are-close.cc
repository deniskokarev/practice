// https://leetcode.com/problems/determine-if-two-strings-are-close/
constexpr char A = 'a';
constexpr int ASZ = 26;

class Solution {
public:
	static bool closeStrings(const string &word1, const string &word2) {
		int c1[ASZ]{0};
		int c2[ASZ]{0};
		for (unsigned char c: word1)
			c1[(c - A) % ASZ]++;
		for (unsigned char c: word2)
			c2[(c - A) % ASZ]++;
		bool ans = true;
		for (int i = 0; i < ASZ; i++)
			ans &= (c1[i] > 0) == (c2[i] > 0);
		sort(c1, c1 + ASZ);
		sort(c2, c2 + ASZ);
		for (int i = 0; i < ASZ; i++)
			ans &= c1[i] == c2[i];
		return ans;
	}
};


class Solution {
public:
    bool closeStrings(const string &word1, const string &word2) {
        vector<int> hist1(26);
        vector<int> hist2(26);
        for (char c:word1)
            hist1[c-'a']++;
        for (char c:word2)
            hist2[c-'a']++;
        sort(hist1.begin(), hist1.end());
        sort(hist2.begin(), hist2.end());
        string set1(word1);
        string set2(word2);
        sort(set1.begin(), set1.end());
        sort(set2.begin(), set2.end());
        int sz;
        sz = unique(set1.begin(), set1.end())-set1.begin();
        set1.resize(sz);
        sz = unique(set2.begin(), set2.end())-set2.begin();
        set2.resize(sz);
        return hist1 == hist2 && set1 == set2;
    }
};
