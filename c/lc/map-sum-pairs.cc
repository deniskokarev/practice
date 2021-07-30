// https://leetcode.com/problems/map-sum-pairs/
// very fast trie-based solution

constexpr int ALPHABET = 26;
constexpr int MXLEN = 50;

class MapSum {
	struct Node {
		array<int,ALPHABET> nxt {0};
		int v {0};
		int sm {0};
	};
	vector<Node> nodes;

public:
	MapSum():nodes(2) { // root starts with ofs=1
	}
	
	void insert(const string &key, int v) {
		int root = 1;
		int path[MXLEN] = {root};
		int path_sz = 1;
		for (auto c: key) {
			int idx = c - 'a';
			if (nodes[root].nxt[idx] == 0) {
				nodes[root].nxt[idx] = nodes.size();
				nodes.push_back(Node());
			}
			root = nodes[root].nxt[idx];
			path[path_sz++] = root;
		}
		int diff = v - nodes[root].v;
		nodes[root].v = v;
		for (int i=0; i<path_sz; i++)
			nodes[path[i]].sm += diff;
	}
	
	int sum(const string &prefix) const {
		int root = 1;
		for (auto c: prefix)
			root = nodes[root].nxt[c - 'a']; // it's ok to loop in node 0
		return nodes[root].sm;
	}
};

