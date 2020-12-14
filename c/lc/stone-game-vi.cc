class Solution {
    struct D {
        int sm;
        int score[2];
        bool operator<(const D &o) const {
            return sm < o.sm;
        }
    };
public:
    int stoneGameVI(const vector<int>& av, const vector<int>& bv) {
        int sz = av.size();
        priority_queue<D> pq;
        for (int i=0; i<sz; i++)
            pq.push(D {av[i]+bv[i], {av[i], bv[i]}});
        int score[2]{0};
        int turn = 0;
        while (!pq.empty()) {
            score[turn] += pq.top().score[turn];
            pq.pop();
            turn ^= 1;
        }
        return (score[0]>score[1]) - (score[0]<score[1]);                    
    }
};
