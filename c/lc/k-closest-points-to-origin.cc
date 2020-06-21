// https://leetcode.com/problems/k-closest-points-to-origin

using T = vector<int>;

bool operator<(const T &a, const T &b) {
	return a[0]*a[0] + a[1]*a[1] < b[0]*b[0] + b[1]*b[1];
}

bool operator==(const T &a, const T &b) {
	return a[0]*a[0] + a[1]*a[1] == b[0]*b[0] + b[1]*b[1];
}

class Solution {
public:
	// my own Kth order statistic (nth_element)
	static vector<vector<int>> kClosest(vector<vector<int>>& vv, int k) {
		int l=0, r=vv.size()-1;
		int sz = r-l+1;
		k--;
		while (sz>2) {
			// lt - first eq, eq - last eq or first gt:
			// assertion vv[lt] == pivot && lt<=eq && vv[eq-1] == pivot && vv[eq] >= pivot
			int lt=l, eq=l+1, gt=r; 
			// arrange base 3 elements
			if (vv[eq]<vv[lt])
				swap(vv[lt], vv[eq]);
			if (vv[gt]<vv[eq])
				swap(vv[eq], vv[gt]);
			if (vv[eq]<vv[lt])
				swap(vv[lt], vv[eq]);
			const T pivot = vv[eq];
			if (vv[lt] < pivot)
				lt++;
			while (eq < gt) {
				while (eq < gt && !(pivot < vv[eq])) {
					while (eq < gt && vv[eq] == pivot)
						eq++;
					if (vv[eq] < pivot)
						swap(vv[lt++], vv[eq]);
				}
				while (pivot < vv[gt])
					gt--;
				assert(vv[lt] == pivot && lt<=eq && vv[eq-1] == pivot && !(vv[eq] < pivot));
				if (eq < gt)
					swap(vv[eq], vv[gt]);
				else if (vv[eq] < pivot)
					swap(vv[lt++], vv[eq]);
			}
			if (lt <= k && k <= eq-1)
				break;
			else if (k >= eq)
				l = eq;
			else if (k < lt)
				r = lt-1;
			sz = r-l+1;
		}
		if (sz == 2 && vv[r] < vv[l])
			swap(vv[l], vv[r]);
		vv.resize(k+1);
		return vv;
	}
};

