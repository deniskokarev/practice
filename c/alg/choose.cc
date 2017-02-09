#include <iostream>
#include <vector>
#include <cassert>

typedef void(*F)(const std::vector<int> &v, const std::vector<int> &cpos);

static void choose_r(const std::vector<int> &v,
					 std::vector<int> &cpos,
					 int beg,
					 int lvl,
					 const F &f) {
	if (!lvl) {
		f(v, cpos);
	} else {
		for (int i=beg; i<v.size(); ++i) {
			cpos.push_back(i);
			choose_r(v, cpos, i+1, lvl-1, f);
			cpos.pop_back();
		}
	}
}

void choose(const std::vector<int> &v, int k, const F &f) {
	std::vector<int> cpos;
	assert(k <= v.size());
	choose_r(v, cpos, 0, k, f);
}

int main(int argc, char **argv) {
	std::vector<int> n = {1, 2, 3, 4, 5};
	choose(n, 3,
		[](const std::vector<int> &v, const std::vector<int> &cpos) -> void {
			if (cpos.size() > 0) {
				for(std::vector<int>::const_iterator i=cpos.begin(); i!=cpos.end()-1; ++i)
					std::cout << v[*i] << ", ";
				std::cout << v[cpos.back()] << std::endl;
			}
		}
	);
	return 0;
}
