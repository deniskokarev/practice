#include <iostream>
#include <vector>
#include <list>
/* https://leetcode.com/problems/reverse-nodes-in-k-group */
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
		vector<ListNode*> invbuf(k);
		ListNode *it = head;
		ListNode res(-1);
		ListNode **out = &res.next;
		while (it) {
			int i = 0;
			while (it && i<k) {
				invbuf[i] = it;
				it = it->next;
				i++;
			}
			if (i==k) {
				*out = invbuf[i-1];
				for (int j=i-1; j>0; j--)
					invbuf[j]->next = invbuf[j-1];
				out = &invbuf[0]->next;
				*out = nullptr;
			} else {
				*out = invbuf[0];
			}
		}
		return res.next;
    }
};

static void test1() {
}

int main() {
	test1();
	return 0;
}
