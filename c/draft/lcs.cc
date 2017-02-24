/*
 * LCS - longest common subsequence
 */
#include <string>
#include <vector>
#include <stack>
#include <iostream>	// TODO: remove

namespace lcs {
	
	namespace details {
		
		struct entry {
			size_t sz;
			int a, b;
			int na, nb;
			entry():sz(0),a(-1),b(-1),na(-1),nb(-1){}
			entry(int aa, int ab, const entry &e):sz(e.sz+1),a(aa),b(ab),na(e.a),nb(e.b){}
		};

		static void lcs_r(const std::string &a, int pa, const std::string &b, int pb, std::vector<std::vector<entry> > &cache) {
			if (pa < a.size() && pb < b.size() && cache[pa][pb].a < 0) {
				if (a[pa] == b[pb]) {
					lcs_r(a, pa+1, b, pb+1, cache);
					cache[pa][pb] = entry(pa, pb, cache[pa+1][pb+1]);
				} else {
					lcs_r(a, pa+1, b, pb, cache);
					lcs_r(a, pa, b, pb+1, cache);
					if (cache[pa+1][pb].sz > cache[pa][pb+1].sz)
						cache[pa][pb] = cache[pa+1][pb];
					else
						cache[pa][pb] = cache[pa][pb+1];
				}
			}
		}

		static std::vector<std::pair<int,int> > reconstruct(const std::vector<std::vector<entry> > &cache) {
			std::vector<std::pair<int,int> > res;
			int na, nb;
			na = nb = 0;
			while (na >=0 && nb >= 0) {
				const entry &e = cache[na][nb];
				res.push_back(std::pair<int,int>(e.a, e.b));
				na = e.na;
				nb = e.nb;
			}
			return res;
		}
	}

	using namespace details;
	
	std::vector<std::pair<int,int> > lcs(const std::string &a, const std::string &b) {
		std::vector<std::vector<entry> > cache(a.size()+1, std::vector<entry>(b.size()+1));
		lcs_r(a, 0, b, 0, cache);
		return reconstruct(cache);
	}
}

int main(int argc, char **argv) {
	std::string a;
	std::string b;
	std::cin >> a;
	std::cin >> b;
	std::vector<std::pair<int,int> > result = lcs::lcs(a, b);
	std::cout << result.size() << std::endl;
	for (std::vector<std::pair<int,int> >::iterator it=result.begin(); it!=result.end(); ++it)
		std::cout << a[it->first];
	std::cout << std::endl;
}
