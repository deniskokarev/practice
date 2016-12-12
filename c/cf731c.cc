#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>

struct Pair {
	int left, right;
	Pair(int l, int r) {
		left = std::min(l, r);
		right = std::max(l, r);
	}
};

struct Input {
	int nsocks;
	int ndays;
	int ncolors;
	std::vector<int> color;
	std::vector<Pair> pair;
	Input(std::istream &is) {
		is >> nsocks;
		is >> ndays;
		is >> ncolors;
		color.reserve(nsocks);
		for (int i=0; i<nsocks; i++) {
			int c;
			is >> c;
			color[i] = c-1;
		}
		for (int i=0; i<ndays; i++) {
			int l, r;
			is >> l;
			is >> r;
			pair.push_back(Pair(l-1, r-1));
		}
	}
};

struct DAGNode {
	bool mark;
	int sock;
	int color;
	std::map<int, DAGNode*> chld;
	DAGNode(int asock, int acolor):mark(false),sock(asock),color(acolor) {
	}
	void add(DAGNode *c) {
		if (!chld.count(c->sock))
			chld.emplace(c->sock, c);
	}
};

struct Answer {
	int cnt;
	std::vector<int> nc;
	Answer(int ncolors):cnt(0),nc(ncolors) {
		next();
	}
	void next() {
		cnt = 0;
		std::fill(nc.begin(), nc.end(), 0);
	}
};

void walk(DAGNode *root, Answer &ans) {
	if (root && !root->mark) {
		root->mark = true;
		for (auto c:root->chld)
			walk(c.second, ans);
		ans.cnt++;
		ans.nc[root->color]++;
	}
}

int main(int argc, char **argv) {
	Input in(std::cin);
	std::vector<std::unique_ptr<DAGNode>> socks(in.nsocks);
	for (auto p:in.pair) {
		if (socks[p.left] == nullptr)
			socks[p.left] = std::unique_ptr<DAGNode>(new DAGNode(p.left, in.color[p.left]));
		if (socks[p.right] == nullptr)
			socks[p.right] = std::unique_ptr<DAGNode>(new DAGNode(p.right, in.color[p.right]));
		socks[p.left]->add(socks[p.right].get());
	}
	Answer ans(in.ncolors);
	int res = 0;
	for (std::vector<std::unique_ptr<DAGNode>>::iterator dn=socks.begin(); dn!=socks.end(); ++dn) {
		walk(dn->get(), ans);
		res += ans.cnt - *std::max_element(ans.nc.begin(), ans.nc.end());
		ans.next();
	}
	std::cout << res << std::endl;
	return 0;
}
