// https://leetcode.com/problems/remove-zero-sum-consecutive-nodes-from-linked-list

class Solution {
    // quadratic
public:
    ListNode* removeZeroSumSublists(ListNode* head) {
        map<int,vector<ListNode*>> sm_p;
        int sm = 0;
        ListNode h;
        h.next = head;
        sm_p[0].push_back(&h);
        for (auto n=head; n; n=n->next) {
            sm += n->val;
            for (auto rn:sm_p[sm]) {
                rn->next = n->next;
            }
            sm_p[sm].push_back(n);
        }
        return h.next;
    }
};

class Solution {
    // linear
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
