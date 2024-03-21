// https://leetcode.com/problems/reverse-linked-list
class Solution {
public:
    static ListNode* reverseList(ListNode* h) {
        ListNode *t = nullptr;
        while (h) {
            auto n = h->next;
            h->next = t;
            t = h;
            h = n;
        }
        return t;        
    }
};
