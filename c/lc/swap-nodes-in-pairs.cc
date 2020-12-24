class Solution {
public:
    ListNode* swapPairs(ListNode* list) {
        ListNode *tail = nullptr, *head = list;
        while (list && list->next) {
            // p1 -> p2 -> list
            ListNode *p1 = list;
            ListNode *p2 = list->next;
            list = p2->next;
            if (tail)
                tail->next = p2; // second+ pair
            else
                head = p2;  // first pair
            p2->next = p1;  // p2 -> p1 -> null
                            //        ^
                            //       tail
            p1->next = nullptr;
            tail = p1;
        }
        if (tail)
            tail->next = list; // take care of last element after at least one pair
        return head;
    }
};
