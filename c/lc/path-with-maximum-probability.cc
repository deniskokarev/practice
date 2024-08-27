// https://leetcode.com/problems/path-with-maximum-probability
class Solution {
    struct E {
        int t;
        double w;

        bool operator<(const E &o) const {
            return w < o.w;
        }
    };

    using G = vector<vector<E>>;
public:
    static double
    maxProbability(int n, const vector<vector<int>> &edges, const vector<double> &succProb, int start_node,
                   int end_node) {
        G gg(n);
        int sz = edges.size();
        for (int i = 0; i < sz; i++) {
            auto pl = log(succProb[i]);
            gg[edges[i][0]].push_back({edges[i][1], pl});
            gg[edges[i][1]].push_back({edges[i][0], pl});
        }
        vector<bool> seen(n);
        priority_queue<E> qq;
        qq.push({start_node, 0});
        while (!qq.empty()) {
            E pos = qq.top();
            qq.pop();
            if (pos.t == end_node) {
                return exp(pos.w);
            }
            if (!seen[pos.t]) {
                seen[pos.t] = true;
                for (auto &e: gg[pos.t]) {
                    qq.push({e.t, pos.w + e.w});
                }
            }
        }
        return 0;
    }
};


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
