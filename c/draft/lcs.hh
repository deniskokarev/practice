/*
 * LCS - longest common subsequence
 */
#include <vector>

namespace lcs {
	
	namespace details {
		
		struct entry {
			int sz;
			int a, b;
			int na, nb;
			entry():sz(0),a(-1),b(-1),na(-1),nb(-1){}
			entry(int _a, int _b, const entry &e):sz(e.sz+1),a(_a),b(_b),na(e.a),nb(e.b){}
		};

		template<typename IT> void lcs_r(const IT &ahead, const IT &aend,
										 const IT &bhead, const IT &bend,
										 std::vector<std::vector<entry> > &cache) {
			IT aa(ahead);
			IT bb(bhead);
			int bi=1;
			std::vector<std::pair<int,int> > res;
			while (bb!=bend) {
				int ai=1;
				for (IT a(aa); a!=aend; ++a) {
					if (*a == *bb) {
						cache[ai][bi] = entry(ai, bi, cache[ai-1][bi-1]);
					} else {
						if (cache[ai-1][bi].sz > cache[ai][bi-1].sz)
							cache[ai][bi] = cache[ai-1][bi];
						else
							cache[ai][bi] = cache[ai][bi-1];
					}
					++ai;
				}
				++bb;
				++bi;
			}
		}

		std::vector<std::pair<int,int> > reconstruct(const std::vector<std::vector<entry> > &cache) {
			std::vector<std::pair<int,int> > res;
			int na = cache.size()-1;
			if (na > 0) {
				int nb = cache[0].size()-1;
				if (cache[na][nb].a >= 0) {
					int di = cache[na][nb].sz-1;
					res.resize(di+1);
					while (na >= 0 && nb >= 0) {
						const entry &e = cache[na][nb];
						res[di] = std::pair<int,int>(e.a-1, e.b-1);
						na = e.na;
						nb = e.nb;
						di--;
					}
				}
			}
			return res;
		}
		template<typename IT> std::ptrdiff_t getsize(const IT &begin, const IT &end, std::random_access_iterator_tag) {
			return end-begin;
		}
		template<typename IT> std::ptrdiff_t getsize(const IT &begin, const IT &end, std::input_iterator_tag) {
			std::ptrdiff_t sz = 0;
			for(IT it(begin); it != end; ++it)
				sz++;
			return sz;
		}
	}

	using namespace details;
	
	template<typename IT, typename OIT> int lcs(const IT &ahead, const IT &aend,
								  const IT &bhead, const IT &bend,
								  OIT dst) {
		std::vector<std::vector<entry> > cache(getsize(ahead, aend, typename std::iterator_traits<IT>::iterator_category())+1,
											   std::vector<entry>(getsize(bhead, bend, typename std::iterator_traits<IT>::iterator_category())+1));
		lcs_r(ahead, aend, bhead, bend, cache);
		std::vector<std::pair<int,int> > res(reconstruct(cache));
		std::copy(res.begin(), res.end(), dst);
		return res.size();
	}
}
