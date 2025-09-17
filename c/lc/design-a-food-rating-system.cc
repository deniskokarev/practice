// https://leetcode.com/problems/design-a-food-rating-system
class FoodRatings {
	struct E {
		string cu;
		int rt;
		string nm;
		bool operator<(const E& e) const {
			return cu < e.cu || cu == e.cu && rt > e.rt || cu == e.cu && rt == e.rt && nm < e.nm;
		}
	};
	using S = set<E>;
	using FK = S::iterator;
	S db;
	map<string, FK> nm2db;
public:
	FoodRatings(vector<string>& foods, vector<string>& cuisines, vector<int>& ratings):db{},nm2db{} {
        int sz = foods.size();
		for (int i = 0; i < sz; i++) {
			FK it;
			std::tie(it, std::ignore) = db.insert({cuisines[i], ratings[i], foods[i]});
			nm2db[foods[i]] = it;
		}
	}

	void changeRating(string food, int newRating) {
		const auto fnd = nm2db.find(food);
		if (fnd != nm2db.end()) {
			auto it = fnd->second;
			const E el = {it->cu, newRating, it->nm};
			db.erase(it);
			bool b;
			std::tie(it, std::ignore) = db.insert(el);
			nm2db[food] = it;
		}
	}

	string highestRated(string cuisine) {
		const E el = {cuisine, INT_MAX, ""};
		auto r = db.upper_bound(el);
		return r->nm;
	}
};

