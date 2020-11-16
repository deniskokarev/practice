class Solution {
public:
	static int minimumDeletions(const string &s) {
		int sz = s.size();
		vector<int> ac(sz); // to delete 'a's from right
		ac[sz-1] = (s[sz-1] == 'a');
		for (int i=sz-2; i>=0; i--)
			ac[i] = ac[i+1] + (s[i] == 'a');
		vector<int> bc(sz); // to delete 'b's from left
		bc[0] = (s[0] == 'b');
		for (int i=1; i<sz; i++)
			bc[i] = bc[i-1] + (s[i] == 'b');
		int mn = INT_MAX;
		for (int i=0; i<sz; i++)
			mn = min(mn, ac[i]+bc[i]);
		return mn-1;
	}
};

