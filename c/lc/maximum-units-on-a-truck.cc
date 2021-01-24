class Solution {
public:
    static int maximumUnits(vector<vector<int>>& boxType, int truckSize) {
        sort(boxType.begin(), boxType.end(), [](const vector<int> &a, const vector<int> &b){return a[1]>b[1];});
        int sm = 0;
        int b = 0;
        while (truckSize && b < boxType.size()) {
            if (truckSize >= boxType[b][0]) {
                truckSize -= boxType[b][0];
                sm += boxType[b][0] * boxType[b][1];
                b++;
            } else {
                sm += truckSize * boxType[b][1];
                truckSize = 0;
            }
        }
        return sm;
    }
};
