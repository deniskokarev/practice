class Solution {
public:
    int minJumps(const vector<int>& aa) {
        constexpr int INF = INT_MAX/2;
        unordered_map<int,list<int>> v2p;
        int sz = aa.size();
        for (int i=0; i<sz; i++)
            v2p[aa[i]].push_back(i);
        vector<int> dist(sz, INF);
        dist[0] = 0;
        queue<int> qq;
        qq.push(0);
        while (!qq.empty()) {
            int p = qq.front();
            qq.pop();
            for (int c:v2p[aa[p]]) {
                if (dist[c] == INF) {
                    dist[c] = dist[p]+1;
                    qq.push(c);
                }
            }
            v2p.erase(aa[p]);
            int c = p+1;
            if (c < sz && dist[c] == INF) {
                dist[c] = dist[p]+1;
                qq.push(c);
            }
            c = p-1;
            if (c >=0 && dist[c] == INF) {
                dist[c] = dist[p]+1;
                qq.push(c);
            }
        }
        return dist[sz-1];
    }
};
