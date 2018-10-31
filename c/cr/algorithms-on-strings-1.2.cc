#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int const Letters =    4;
int const NA      =   -1;

struct Node
{
	int next [Letters];

	Node ()
	{
		fill (next, next + Letters, NA);
	}

	bool isLeaf () const
	{
	    return (next[0] == NA && next[1] == NA && next[2] == NA && next[3] == NA);
	}
};

int letterToIndex (char letter)
{
	switch (letter)
	{
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
		default: assert (false); return -1;
	}
}

using trie = vector<Node>;

trie build_trie(const vector <string>& patterns) {
	trie t(1);
	for (auto &p:patterns) {
		trie::iterator root = t.begin();
		for (auto ch:p) {
			int &ri = root->next[letterToIndex(ch)];
			int i = ri;
			if (i == NA) {
				i = int(t.size());
				ri = i;
				t.resize(i+1);
			}
			root = t.begin()+i;
		}
	}
	return t;
}

vector <int> solve (const string& text, int n, const vector <string>& patterns)
{
	const trie trie = build_trie(patterns);
	vector <int> result;

	for (int h=0; h<text.size(); h++) {
		trie::const_iterator root = trie.cbegin();
		for (int t=h; t<text.size(); t++) {
			int ri = root->next[letterToIndex(text[t])];
			if (ri == NA)
				break;
			root = trie.cbegin()+ri;
			if (root->isLeaf())
				result.push_back(h);
		}
	}
	return result;
}

int main (void)
{
	string t;
	cin >> t;

	int n;
	cin >> n;

	vector <string> patterns (n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
	}

	vector <int> ans;
	ans = solve (t, n, patterns);

	for (int i = 0; i < (int) ans.size (); i++)
	{
		cout << ans[i];
		if (i + 1 < (int) ans.size ())
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}

	return 0;
}
