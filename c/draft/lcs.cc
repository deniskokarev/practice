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

		template<typename IT> void lcs_r(const IT &ahead, const IT &aend, int pa,
										 const IT &bhead, const IT &bend, int pb,
										 std::vector<std::vector<entry> > &cache) {
			if (ahead != aend && bhead != bend && cache[pa][pb].a < 0) {
				IT na = ahead;
				na++;
				IT nb = bhead;
				nb++;
				if (*ahead == *bhead) {
					lcs_r(na, aend, pa+1, nb, bend, pb+1, cache);
					cache[pa][pb] = entry(pa, pb, cache[pa+1][pb+1]);
				} else {
					lcs_r(na, aend, pa+1, bhead, bend, pb, cache);
					lcs_r(ahead, aend, pa, nb, bend, pb+1, cache);
					if (cache[pa+1][pb].sz > cache[pa][pb+1].sz)
						cache[pa][pb] = cache[pa+1][pb];
					else
						cache[pa][pb] = cache[pa][pb+1];
				}
			}
		}

		std::vector<std::pair<int,int> > reconstruct(const std::vector<std::vector<entry> > &cache) {
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
	
	template<typename IT> std::vector<std::pair<int,int> > lcs(const IT &ahead, const IT &aend, const IT &bhead, const IT &bend) {
		std::vector<std::vector<entry> > cache(aend-ahead+1, std::vector<entry>(bend-bhead+1));
		lcs_r(ahead, aend, 0, bhead, bend, 0, cache);
		return reconstruct(cache);
	}
}

int main(int argc, char **argv) {
	std::vector<std::pair<int,int> > result;
	/*
	std::string a;
	std::string b;
	std::cin >> a;
	std::cin >> b;
	result = lcs::lcs(a.begin(), a.end(), b.begin(), b.end());
	std::cout << result.size() << std::endl;
	for (std::vector<std::pair<int,int> >::iterator it=result.begin(); it!=result.end(); ++it)
		std::cout << a[it->first];
	std::cout << std::endl;
	*/
	char a1[32];
	char b1[32];
	fgets(a1, sizeof(a1), stdin);
	fgets(b1, sizeof(b1), stdin);

	result = lcs::lcs(&a1[0], &a1[strlen(a1)-1], &b1[0], &b1[strlen(b1)-1]);
	std::cout << result.size() << std::endl;
	for (std::vector<std::pair<int,int> >::iterator it=result.begin(); it!=result.end(); ++it)
		std::cout << a1[it->first];
	std::cout << std::endl;
	
}
