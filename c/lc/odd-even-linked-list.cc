// https://leetcode.com/problems/odd-even-linked-list/
class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if (!head || !head->next)
            return head;
        ListNode *eo_tail[2] {head, head->next};
        ListNode *ohead = head->next;
        ListNode *n = head->next->next;
        eo_tail[0]->next = nullptr;
        eo_tail[1]->next = nullptr;
        int i = 0;
        while (n) {
            eo_tail[i&1]->next = n;
            eo_tail[i&1] = n;
            ListNode *nn = n->next;
            n->next = nullptr;
            n = nn;
            i++;
        }
        eo_tail[0]->next = ohead;
        return head;
    }
};
