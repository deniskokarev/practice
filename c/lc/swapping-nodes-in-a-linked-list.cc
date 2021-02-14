class Solution {
public:
    ListNode* swapNodes(ListNode* head, int k) {
        int sz = 0;
        for (ListNode *it=head; it; it=it->next)
            sz++;
        ListNode *f = head;
        for (int i=k-1; i; i--)
            f = f->next;
        ListNode *s = head;
        for (int i=sz-k; i; i--)
            s = s->next;
        swap(f->val, s->val);
        return head;
    }
};
