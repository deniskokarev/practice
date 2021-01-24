class Solution {
public:
	static int findKthLargest(vector<int>& nums, int k) {
		// self-made nth_element()
		std::mt19937 rnd(0);
		k = nums.size() - k; // element should be at pos k in asc sorted array
		int f = 0, t = nums.size()-1;
		while (true) {
			// choose mid randomly and place at beg
			int rnd_pos = f + rnd() * (t-f+1) / std::mt19937::max();
			swap(nums[rnd_pos], nums[f]);
			// three-way partitioning so nums[l..h] == mid
			int l = f, h = t;
			int mid = nums[l];
			int i = l+1;
			while (i <= h) {
				if (nums[i] > mid)
					swap(nums[i], nums[h--]);
				else if (nums[i] < mid)
					swap(nums[l++], nums[i]);
				else
					i++;
			}
			// recur until l<=k && k<=h
			if (k > h)
				f = h+1;
			else if (k < l)
				t = l-1;
			else
				break;
		}
		return nums[k];
	}
};
