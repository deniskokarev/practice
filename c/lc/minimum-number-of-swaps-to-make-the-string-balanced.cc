// https://leetcode.com/problems/minimum-number-of-swaps-to-make-the-string-balanced
static int enableFastIO() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        return 0;
}

static const int fastIO = enableFastIO();

class Solution
{
	static int c2n(char c)
	{
		if (c == '[')
		{
			return 1;
		}
		else
		{
			return -1;
		}
	}

public:
	static int minSwaps(const string& s)
	{
		int sz = s.size();
		int i = 0;
		int lc = 0;
		int ans = 0;
		for (int i=0; i<sz; i++)
		{
			lc += c2n(s[i]);
			if (lc < 0)
			{
				ans++;
				lc = 1;
			}
		}
		return ans;
	}
};

