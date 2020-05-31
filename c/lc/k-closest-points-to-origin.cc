// https://leetcode.com/problems/k-closest-points-to-origin
class Solution {
	using PT = vector<int>;
	struct PT_CMP {
		bool operator()(const PT &a, const PT &b) const {
			int da = a[0]*a[0]+a[1]*a[1];
			int db = b[0]*b[0]+b[1]*b[1];
			return da < db;
		}
	};
	template <class T, class S, class C> S& Container(priority_queue<T, S, C>& q) {
		struct HackedQueue : private priority_queue<T, S, C> {
			static S& Container(priority_queue<T, S, C>& q) {
				return q.*&HackedQueue::c;
			}
		};
		return HackedQueue::Container(q);
	}
public:
	vector<PT> kClosest(const vector<PT> &points, int k) {
		vector<PT> ans;
		priority_queue<PT, vector<PT>, PT_CMP> dist;
		for (int i=0; i<k; i++)
			dist.push(points[i]);
		for (int i=k; i<points.size(); i++) {
			dist.push(points[i]);
			dist.pop();
		}
		return Container(dist);
	}
};

