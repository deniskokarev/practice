// https://leetcode.com/problems/remove-nodes-from-linked-list
class Solution {
    static ListNode* rev(ListNode* nd) {
        ListNode *r = nullptr;
        while (nd) {
            auto n = nd->next;
            nd->next = r;
            r = nd;
            nd = n;
        }
        return r;
    }
    static ListNode* asc(ListNode* nd) {
        int mx = -1;
        ListNode h(-1);
        ListNode *t = &h;
        while (nd) {
            auto n = nd->next;
            if (nd->val >= mx) {
                t->next = nd;
                mx = nd->val;
                nd->next = nullptr;
                t = nd;
            }
            nd = n;
        }
        return h.next;
    }
public:
    static ListNode* removeNodes(ListNode* head) {
        auto r = rev(head); 
        r = asc(r);
        r = rev(r);
        return r;
    }
};
