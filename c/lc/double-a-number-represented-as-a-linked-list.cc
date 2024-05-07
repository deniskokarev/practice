// https://leetcode.com/problems/double-a-number-represented-as-a-linked-list/
class Solution {
    static int dit(ListNode* nd) {
        int c = 0;
        if (nd->next)
            c = dit(nd->next);
        int d = (nd->val << 1) + c;
        nd->val = d % 10;
        return d / 10; 
    }
public:
    static ListNode* doubleIt(ListNode* head) {
        int c = dit(head);
        if (c) {
            return new ListNode(c, head);
        } else {
            return head;
        }
    }
};
