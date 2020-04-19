class Solution {
public:
    ListNode* removeZeroSumSublists(ListNode* head) {
        unordered_map<int,ListNode*> smap;
        stack<int> vals;
        ListNode hd(0);
        hd.next = head;
        int sm = 0;
        smap[0] = &hd;
        vals.push(0);
        while (head) {
            sm += head->val;
            auto fnd = smap.find(sm);
            if (fnd != smap.end()) {
                fnd->second->next = head->next;
                while (vals.top() != sm) {
                    smap.erase(vals.top());
                    vals.pop();
                }
            } else {
                smap[sm] = head;
                vals.push(sm);
            }
            head = head->next;
        }
        return hd.next;
    }
};
