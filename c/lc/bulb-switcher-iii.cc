static void fw_inc(vector<int> &fw, int p, int inc) {
        int sz = fw.size();
        for (int i=p; i<sz; i|=i+1)
                fw[i] += inc;
}

static int fw_sum(const vector<int> &fw, int p) {
        int sz = fw.size();
        int sum = 0;
        for (int i=p; i>=0; i=(i&(i+1))-1)
                sum += fw[i];
        return sum;
}

class Solution {
public:
    int numTimesAllBlue(vector<int>& light) {
        int sz = light.size();
        vector<int> fw(sz+1);
        int cnt = 0;
        int ans = 0;
        for (int t=0; t<sz; t++) {
            int l = light[t];
            fw_inc(fw, l, 1);
            if (fw_sum(fw, t+1) == t+1)
                ans++;
        }
        return ans;
    }
};
