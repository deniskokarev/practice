namespace treap {
	
	enum {L, R};

	using LR = std::array<int,2>;

	struct TreapNode {
		int val;
		std::mt19937::result_type pri;
		int cnt;
		LR lr;
	};

	struct Treap {
		std::vector<TreapNode> treap;
		std::mt19937 rnd;
	
		Treap():treap{{INT_MIN,0,0,{{0,0}}}},rnd(0) {
		}

		LR splice(int root, int val) {
			if (root) {
				if (treap[root].val >= val) {
					treap[root].cnt -= treap[treap[root].lr[L]].cnt;
					LR sroot = splice(treap[root].lr[L], val);
					treap[root].lr[L] = sroot[R];
					treap[root].cnt += treap[sroot[R]].cnt;
					return {{sroot[L], root}};
				} else {
					treap[root].cnt -= treap[treap[root].lr[R]].cnt;
					LR sroot = splice(treap[root].lr[R], val);
					treap[root].lr[R] = sroot[L];
					treap[root].cnt += treap[sroot[L]].cnt;
					return {{root, sroot[R]}};
				}
			} else {
				return {{0,0}};
			}
		}
	
		void insert(int val) {
			int node = treap.size();
			treap.push_back(TreapNode{val, rnd(), 1, {{0, 0}}});
			int root = treap[0].lr[L];
			int p = 0;
			int lr = L;
			while (root && treap[root].pri > treap[node].pri) {
				treap[root].cnt++;
				p = root;
				lr = (treap[root].val < treap[node].val);
				root = treap[root].lr[lr];
			}
			treap[node].lr = splice(root, val);
			treap[node].cnt += treap[treap[node].lr[L]].cnt + treap[treap[node].lr[R]].cnt;
			treap[p].lr[lr] = node;
		}

		int size() {
			return treap.size()-1;
		}
		
		int nth_node(int n) {
			int root = treap[0].lr[L];
			while (root) {
				if (treap[treap[root].lr[L]].cnt == n) {
					break;
				} else if (treap[treap[root].lr[L]].cnt < n) {
					n -= treap[treap[root].lr[L]].cnt+1;
					root = treap[root].lr[R];
				} else {
					root = treap[root].lr[L];
				}
			}
			return root;
		}

		int nth_val(int n) {
			return treap[nth_node(n)].val;
		}

		void dbg_prn() {
			for (int i=0; i<treap.size(); i++) {
				auto &n = treap[i];
				std::cerr << "[idx=" << i << " val=" << n.val << " cnt=" << n.cnt << " (" << n.lr[L] << "," << n.lr[R] << ")] ";
			}
			std::cerr << '\n';
		}

		void dfs_prn_r(int root) {
			if (root) {
				dfs_prn_r(treap[root].lr[L]);
				std::cerr << treap[root].val << ' ';
				dfs_prn_r(treap[root].lr[R]);
			}
		}

		void ord_prn() {
			dfs_prn_r(treap[0].lr[L]);
		}
	};
}

using namespace std;

class MedianFinder {
	treap::Treap treap;
public:
	/** initialize your data structure here. */
	MedianFinder():treap() {
	}
	
	void addNum(int num) {
		treap.insert(num);
	}
	
	double findMedian() {
		int sz = treap.size();
		if (sz&1) {
			return treap.nth_val(sz/2);
		} else {
			int h = sz/2;
			return (double(treap.nth_val(h-1)) + treap.nth_val(h))/2;
		}
	}
};

