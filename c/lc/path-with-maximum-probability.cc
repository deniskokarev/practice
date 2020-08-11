class Solution {
    struct E {
        int t;
        double p;
    };
    struct Q {
        double p;
        int node;
        bool operator<(const Q &o) const {
            return p < o.p;
        }
    };
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {
        vector<vector<E>> gr(n);
        int e_sz = edges.size();
        for (int i=0; i<e_sz; i++) {
            gr[edges[i][0]].push_back(E{edges[i][1],succProb[i]});
            gr[edges[i][1]].push_back(E{edges[i][0],succProb[i]});
        }
        vector<bool> seen(n, false);
        priority_queue<Q> pq;
        pq.push(Q{1.0,start});
        while (!pq.empty()) {
            Q top = pq.top();
            pq.pop();
            if (top.node == end)
                return top.p;
            if (!seen[top.node]) {
                seen[top.node] = true;
                for (auto e:gr[top.node])
                    pq.push(Q{top.p*e.p, e.t});
            }
        }
        return 0;
    }
};
