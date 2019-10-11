#include <iostream>
#include <vector>
#include <list>
/* https://leetcode.com/problems/merge-k-sorted-lists */
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    static ListNode* mergeKLists(vector<ListNode*>& lists) {
		int sz = int(lists.size());
        if (sz < 1)
            return nullptr;
		vector<ListNode*> it(sz);
		vector<pair<int,int>> hh(2*sz);
		for (int i=0; i<sz; i++) {
			it[i] = lists[i];
			if (it[i] != nullptr) {
				hh[i+sz] = make_pair(it[i]->val, i);
				it[i] = it[i]->next;
			} else {
				hh[i+sz] = make_pair(INT_MAX, i);
			}
		}
		for (int i=2*sz-1; i>1; i-=2) {
			int r = i/2;
			hh[r] = std::min(hh[i], hh[i-1]);
		}
		ListNode res(-1);
		ListNode **eres = &res.next;
		while (hh[1].first < INT_MAX) {
			ListNode *node = new ListNode(hh[1].first);
			*eres = node;
			eres = &node->next;
			int c = hh[1].second;
			if (it[c] != nullptr) {
				hh[c+sz] = make_pair(it[c]->val, c);
				it[c] = it[c]->next;
			} else {
				hh[c+sz] = make_pair(INT_MAX, c);
			}
			c += sz;
			while (c>1) {
				int r = c/2;
				hh[r] = std::min(hh[c], hh[c^1]);
				c = r;
			}
		}
		return res.next;
    }
	
	static list<int> mergeKLists(vector<list<int>>& lists) {
		int sz = int(lists.size());
		list<int> res;
		if (sz < 1)
			return res;
		vector<list<int>::iterator> it(sz);
		vector<list<int>::iterator> ee(sz);
		vector<pair<int,int>> hh(2*sz);
		for (int i=0; i<sz; i++) {
			it[i] = lists[i].begin();
			ee[i] = lists[i].end();
			if (it[i] != ee[i]) {
				hh[i+sz] = make_pair(*it[i], i);
				++it[i];
			} else {
				hh[i+sz] = make_pair(INT_MAX, i);
			}
		}
		for (int i=2*sz-1; i>1; i-=2) {
			int r = i/2;
			hh[r] = std::min(hh[i], hh[i-1]);
		}
		while (hh[1].first < INT_MAX) {
			cerr << hh[1].first << ' ';
			res.push_back(hh[1].first);
			int c = hh[1].second;
			if (it[c] != ee[c]) {
				hh[c+sz] = make_pair(*it[c], c);
				++it[c];
			} else {
				hh[c+sz] = make_pair(INT_MAX, c);
			}
			c += sz;
			while (c>1) {
				int r = c/2;
				hh[r] = std::min(hh[c], hh[c^1]);
				c = r;
			}
		}
		cerr << '\n';
		return res;
    }
};

static void test1() {
	vector<list<int>> ll {{1,4,5}, {1,3,4}, {2,6}}; 
	Solution::mergeKLists(ll);
}

int main() {
	test1();
	return 0;
}
