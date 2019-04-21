#include <iostream>
#include <vector>
#include <queue>
/* https://leetcode.com/problems/stream-of-characters/ */
using namespace std;

#define ACT_ROOT	1

#define ACT_PAGE_P2		8

struct ACT_NODE_COMP {
	unsigned next[1<<ACT_PAGE_P2] {0};
	unsigned sufref {0};
	int val {0};
	unsigned parent {0};
	char end {0};
	unsigned char ch {0};
};

typedef struct tag_ACT_NODE {
	unsigned next[1<<ACT_PAGE_P2]; // where to go upon next char
	unsigned sufref; // continue to next match
	int val:31;
	unsigned char end:1;
} ACT_NODE;

typedef struct tag_ACT {
	ACT_NODE *nodes;
	size_t sz;
	int fd;
	const char *fname;
} ACT;

void act_insert(std::vector<ACT_NODE_COMP> &nodes, const unsigned char *s, unsigned s_sz, int val) {
	unsigned root = ACT_ROOT;
	while (s_sz--) {
		unsigned bmask = *s++;
		for (int i=0; i<8/ACT_PAGE_P2; i++,bmask>>=ACT_PAGE_P2) {
			unsigned char bch = bmask & ((1<<ACT_PAGE_P2)-1);
			unsigned nroot = nodes[root].next[bch];
			if (nroot == 0) {
				nroot = int(nodes.size());
				nodes.resize(nodes.size()+1); // will call node constructor
				nodes[nroot].ch = bch;
				nodes[nroot].parent = root;
				nodes[root].next[bch] = nroot;
			}
			root = nroot;
		}
	}
	nodes[root].val = val;
	nodes[root].end = 1;
}

void act_build_sufref(std::vector<ACT_NODE_COMP> &nodes) {
	std::queue<unsigned> qq;
	// init root and its immediate children
	// start BFS on grandchildren
	nodes[ACT_ROOT].sufref = ACT_ROOT;
	for (unsigned next:nodes[ACT_ROOT].next) {
		if (next) {
			nodes[next].sufref = ACT_ROOT;
			for (unsigned nn:nodes[next].next)
				if (nn)
					qq.push(nn);
		}
	}
	while (!qq.empty()) {
		unsigned root = qq.front();
		qq.pop();
		unsigned char ch = nodes[root].ch;
		unsigned psf = nodes[nodes[root].parent].sufref;
		while (psf != ACT_ROOT && nodes[psf].next[ch] == 0)
			psf = nodes[psf].sufref;
		if (nodes[psf].next[ch] != 0)
			nodes[root].sufref = nodes[psf].next[ch];
		else
			nodes[root].sufref = ACT_ROOT; // couldn't find suffix
		for (unsigned next:nodes[root].next)
			if (next)
				qq.push(next);
	}
}

void act_fill_all_next(std::vector<ACT_NODE_COMP> &nodes) {
	std::queue<unsigned> qq;
	qq.push(ACT_ROOT);
	while (!qq.empty()) {
		unsigned root = qq.front();
		qq.pop();
		for (unsigned next:nodes[root].next)
			if (next)
				qq.push(next);
		for (unsigned ch=0; ch<(1<<ACT_PAGE_P2); ch++) {
			if (nodes[root].next[ch] == 0) {
				unsigned sr = nodes[root].sufref;
				if (nodes[sr].next[ch])
					nodes[root].next[ch] = nodes[sr].next[ch];
				else
					nodes[root].next[ch] = ACT_ROOT;
			}
		}
	}
}

void act_build_direct_sufref(std::vector<ACT_NODE_COMP> &nodes) {
	std::vector<char> seen(nodes.size(), 0);
	std::queue<unsigned> qq;
	qq.push(ACT_ROOT);
	seen[ACT_ROOT] = 1;
	while (!qq.empty()) {
		unsigned root = qq.front();
		qq.pop();
		if (root != ACT_ROOT && nodes[root].parent != ACT_ROOT) {
			if (!nodes[nodes[root].sufref].end)
				nodes[root].sufref = nodes[nodes[root].sufref].sufref;
		}
		for (unsigned next:nodes[root].next)
			if (next && !seen[next])
				qq.push(next), seen[next] = 1;
	}
}

class StreamChecker {
	std::vector<ACT_NODE_COMP> nodes;
	std::vector<string> adds;
	int n;
public:
    StreamChecker(const vector<string>& words):nodes(2),adds(words),n(ACT_ROOT) {
		for (auto s:adds) {
			s += '\0'; // add 0-term
			act_insert(nodes, (const unsigned char*)s.c_str(), s.size()-1, 1);
		}
		act_build_sufref(nodes);
		act_fill_all_next(nodes);
		act_build_direct_sufref(nodes);
    }
    
    bool query(char letter) {
		n = nodes[n].next[letter];
		for (unsigned en=n; en != ACT_ROOT; en=nodes[en].sufref)
			if (nodes[en].end)
				return true;
		return false;
    }
};

int main(int argc, char **argv) {
	cout << "real answer" << endl;
	return 0;
}
