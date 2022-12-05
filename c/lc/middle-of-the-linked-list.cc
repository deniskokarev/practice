// https://leetcode.com/problems/middle-of-the-linked-list/

class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        auto m = head;
        auto t = m;
        while (t && t->next) {
            t = t->next->next;
            m = m->next;
        }
        return m;
    }
};
