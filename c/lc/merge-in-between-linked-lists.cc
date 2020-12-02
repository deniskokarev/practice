class Solution {
public:
    ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {
        ListNode res(0, list1);
        ListNode *head = &res;
        int i;
        for (i=0; i<a; i++)
            head = head->next;
        ListNode *beg = head;
        for (; i<=b; i++)
            head = head->next;
        beg->next = list2;
        ListNode *end2 = list2;
        while (end2->next)
            end2 = end2->next;
        end2->next = head->next;
        return res.next;
    }
};
