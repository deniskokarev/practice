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

static int betterHlp(int maxWeight,
					 int i,
					 std::vector<Item>::iterator it,
					 const std::vector<Item>::iterator &end,
					 std::vector<int> &res)
{
	if (it == end)
		return 0;
	Item &item = *it;
	std::vector<int> resWith;
	resWith.push_back(i);
	int valWith;
	++it;
	if (item.weight <= maxWeight)
		valWith = betterHlp(maxWeight-item.weight, i+1, it, end, resWith) + item.value;
	else
		valWith = -1;
	std::vector<int> resWithout;
	int valWithout = betterHlp(maxWeight, i+1, it, end, resWithout);
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

int ks::dp(int maxWeight, std::vector<Item> &items) {
	std::vector<std::vector<int>> cache;
	int n = 0;
	cache.resize(n+1);
	cache[n].resize(maxWeight+1);
	for (auto &im:items) {
		n++;
		cache.resize(n+1);
		cache[n].resize(maxWeight+1);
		for (int w=0; w<=maxWeight; w++) {
			if (im.weight <= w)
				cache[n][w] = std::max(cache[n-1][w-im.weight]+im.value, cache[n-1][w]);
			else
				cache[n][w] = cache[n-1][w];
		}
	}
	return cache[n][maxWeight];
}
