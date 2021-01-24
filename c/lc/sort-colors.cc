class Solution {
public:
	static void sortColors(vector<int>& nums) {
		int mid = 1;
		int sz = nums.size();
		int i;
		// place mid element at position l=0
		for (i = 0; i < sz && nums[i] != mid; i++);
		if (i < sz)
			swap(nums[0], nums[i]);
		// nums[l..h] == mid
		int h = sz-1; // [h+1... > mid
		int l = 0;	  // ...l-1] < mid
		i = 0;
		while (i <= h) {
			if (nums[i] < mid)
				swap(nums[l++], nums[i++]);
			else if (nums[i] > mid)
				swap(nums[i], nums[h--]);
			else
				i++;
		}
	}
};
