using P = pair<int,ListNode*>;

/**
 *    r
 *  lc  rc
 */
void my_sift(vector<P> &heap, int sz, int r) {
    int lc = r*2;
    int rc = lc+1;
    int c;
    if (rc <= sz) {
        if (heap[lc] < heap[rc])
            c = lc;
        else
            c = rc;
    } else if (lc <= sz) {
        c = lc;        
    } else {
        return;
    }
    if (heap[r] > heap[c]) {
        swap(heap[r], heap[c]);
        my_sift(heap, sz, c);
    }
}

void my_heapify(vector<P> &heap, int sz) {
    for (int i=sz/2; i>0; i--)
        my_sift(heap, sz, i);
}

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode res;
        ListNode *tail = &res;
        vector<P> heap(lists.size()+1);
        int sz = 0;
        for (int i=0; i<lists.size(); i++)
            if (lists[i])
                heap[++sz] = {lists[i]->val, lists[i]};
        my_heapify(heap, sz);
        while (sz) {
            auto l = heap[1].second;
            auto cn = l->next;
            l->next = nullptr;
            tail->next = l;
            tail = l;
            if (cn)
                heap[1] = {cn->val, cn};
            else
                heap[1] = heap[sz--];
            my_sift(heap, sz, 1);
        }
        return res.next;
    }
};
