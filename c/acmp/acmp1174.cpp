/* ACMP 1174 */
#include <iostream>
#include <memory>
#include <vector>
#include <cassert>

using namespace std;

struct Trie {
	unique_ptr<Trie> node['z'-'a'];
	pair<int,int> pos;
	
	Trie *operator[](char ch) {
		assert(ch >= 'a' && ch <= 'z');
		int ni = ch-'a';
		if (!node[ni])
			node[ni] = unique_ptr<Trie>(new Trie());
		return node[ni].get();
	}
};

int main(int argc, char **argv) {
	int n, m;
	string s;
	cin >> n >> m >> s;
	int l = s.length()/m;
	vector<pair<int,int>> pos; // (prev,val)
	Trie root;
	for (int i=0; i<m; i++) {
		string ms;
		cin >> ms;
		Trie *np = &root;
		for (char ch:ms)
			np = (*np)[ch];
		pos.push_back(np->pos);
		np->pos = make_pair(pos.size()-1, i);
	}
	for (int i=0; i<s.length()/l; i++) {
		Trie *np = &root;
		for (int j=0,p=i*l; j<l; j++,p++)
			np = (*np)[s[p]];
		auto &vv = np->pos;
		cout << vv.second+1 << ' ';
		vv = pos[vv.first];
	}
	cout << endl;
	return 0;
}
