// https://leetcode.com/problems/partition-list/
class Solution {
public:
    ListNode* partition(ListNode* ll, int x) {
        ListNode res = {};
        ListNode *lt = &res;
        ListNode b(0, ll);
        auto it = &b;
        while (it) {
            auto nx = it->next;
            if (nx != nullptr && nx->val < x) {
                it->next = nx->next;
                lt->next = nx;
                nx->next = nullptr;
                lt = nx;
            } else {
                it=it->next;
            }
        }
        lt->next = b.next;
        return res.next;
    }
};
