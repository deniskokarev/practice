#include "knapsack.hh"

using namespace ks;

static int naiveHlp(int maxWeight, std::vector<Item> &src, std::vector<int> &res) {
	int bestVal = 0;
	std::vector<int> bestRes;
	int i = 0;
	for (auto &item: src) {
		if (!item.taken && maxWeight >= item.weight) {
			item.taken = true;
			std::vector<int> justRes;
			int val = naiveHlp(maxWeight-item.weight, src, justRes);
			if (bestVal < val+item.value) {
				bestVal = val+item.value;
				bestRes = justRes;
				bestRes.push_back(i);
			}
			item.taken = false;
		}
		i++;
	}
	res = bestRes;
	return bestVal;
}

int ks::naive(int maxWeight, std::vector<Item> &items) {
	std::vector<int> res;
	int rc = naiveHlp(maxWeight, items, res);
	for (auto i:res)
		items[i].taken = true;
	return rc;
}

static int betterHlp(int maxWeight, int i, std::vector<Item>::iterator it, const std::vector<Item>::iterator &end, std::vector<int> &res) {
	if (it == end)
		return 0;
	Item &item = *it;
	std::vector<int> resWith;
	resWith.push_back(i);
	int valWith;
	std::vector<int> resWithout;
	++it;
	int valWithout = betterHlp(maxWeight, i+1, it, end, resWithout);
	if (item.weight <= maxWeight)
		valWith = betterHlp(maxWeight-item.weight, i+1, it, end, resWith) + item.value;
	else
		valWith = -1;
	if (valWith > valWithout) {
		res = resWith;
		return valWith;
	} else {
		res = resWithout;
		return valWithout;
	}
}

int ks::better(int maxWeight, std::vector<Item> &items) {
	std::vector<int> res;
	int rc = betterHlp(maxWeight, 0, items.begin(), items.end(), res);
	for (auto i:res)
		items[i].taken = true;
	return rc;
}
