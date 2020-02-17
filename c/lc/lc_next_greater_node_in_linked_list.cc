#include <iostream>
#include <vector>
#include <set>
/* next-greater-node-in-linked-list */
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    vector<int> nextLargerNodes(ListNode* head) {
        vector<int> ll;
		for (auto it = head; it != nullptr; it=it->next)
			ll.push_back(it->val);
		set<int> mx;
		mx.insert(INT_MIN);
		for (int i=ll.size()-1; i>=0; i--) {
			auto fnd = mx.upper_bound(ll[i]);
			int res = 0;
			if (fnd != mx.end())
				res = *fnd;
			mx.insert(ll[i]);
			auto p = fnd;
			fnd = prev(mx.find(ll[i]));
			while (fnd != mx.begin()) {
				p = prev(fnd);
				mx.erase(fnd);
				fnd = p;
			}
			ll[i] = res;
		}
		return ll;
    }
};

int main(int argc, char **argv) {
	cout << "real answer" << endl;
	return 0;
}
