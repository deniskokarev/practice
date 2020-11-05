/**
 * Binomial coefficient (choose n, k)
 */
uint64_t choose(int n, int k) {
        uint64_t res = 1;
        for (int i=n,j=1; j<=k; i--,j++) {
                res *= i;
                res /= j;
        }
        return res;
}

class Solution {
public:
	static string kthSmallestPath(const vector<int>& destination, int k) {
		int h = destination[0];
		int w = destination[1];
		string sol;
		while (h && w) {
			int64_t r = choose(h+w-1,w-1);
			if (k > r) {
				sol.push_back('V');
				k -= r;
				h--;
			} else {
				sol.push_back('H');
				w--;
			}
		}
		while (w--)
			sol.push_back('H');
		while (h--)
			sol.push_back('V');
		return sol;
	}
};

