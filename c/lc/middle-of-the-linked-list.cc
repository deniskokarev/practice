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

class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode *p1, *p2;
        p1 = p2 = head;
        while (p2->next) {
            p1 = p1->next;
            p2 = p2->next;
            if (p2->next)
                p2 = p2->next;
        }
        return p1;
    }
};
