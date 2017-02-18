#include <vector>

namespace ks {
	struct Item {
		int weight;
		int value;
		bool taken;
		Item(int w, int v): weight{w}, value{v}, taken{false} {}
	};

	int naive(int maxWeight, std::vector<Item> &src);

	int better(int maxWeight, std::vector<Item> &items);

	int dp(int maxWeight, std::vector<Item> &items);
};

