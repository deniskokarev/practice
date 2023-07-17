// https://leetcode.com/problems/add-two-numbers-ii/
class Solution {
    using L = struct {ListNode *l; int sz;};
    L invert(ListNode* l) {
        ListNode *prev = NULL;
        int len = 0;
        while (l) {
            auto n = l->next;
            l->next = prev;
            prev = l;
            l = n;
            len++;
        }
        return {prev, len};
    }
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        auto s1 = invert(l1);
        auto s2 = invert(l2);
        if (s1.sz > s2.sz) {
            swap(s1, s2);
        }
        auto n1 = s1.l;
        auto n2 = s2.l;
        int carry = 0;
        ListNode *ap = nullptr;
        while (n1) {
            auto a = new ListNode();
            a->next = ap;
            a->val = carry + n1->val + n2->val;
            carry = a->val / 10;
            a->val %= 10;
            n1 = n1->next;
            n2 = n2->next;
            ap = a;
        }
        while (n2) {
            auto a = new ListNode();
            a->next = ap;
            a->val = carry + n2->val;
            carry = a->val / 10;
            a->val %= 10;
            n2 = n2->next;
            ap = a;
        }
        if (carry) {
            auto a = new ListNode();
            a->next = ap;
            a->val = carry;
            ap = a;
        }
        return ap;
    }
};
