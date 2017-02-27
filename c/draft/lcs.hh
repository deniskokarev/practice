/*
 * LCS - longest common subsequence
 * Using dynamic programming with O(n*m) complexity and O(n*m) storage size
 * The simplistic flavor of lcs() without actual correspondence uses O(n) storage
 */
#include <vector>

namespace lcs {
	
	namespace details {
		/* implementation details */
		
		struct entry {
			size_t sz;
			size_t a, b;
			size_t na, nb;
			entry():sz(0),a(0),b(0),na(0),nb(0){}
			entry(size_t _b, size_t _a, const entry &e):sz(e.sz+1),a(_a),b(_b),na(e.a),nb(e.b){}
		};

		template<typename IT> void lcs_r(const IT &ahead, const IT &aend,
										 const IT &bhead, const IT &bend,
										 std::vector<std::vector<entry> > &cache) {
			IT bb(bhead);
			size_t bi = 1;
			while (bb != bend) {
				size_t ai = 1;
				for (IT a(ahead); a != aend; ++a) {
					if (*a == *bb) {
						cache[bi][ai] = entry(bi, ai, cache[bi-1][ai-1]);
					} else {
						if (cache[bi][ai-1].sz > cache[bi-1][ai].sz)
							cache[bi][ai] = cache[bi][ai-1];
						else
							cache[bi][ai] = cache[bi-1][ai];
					}
					++ai;
				}
				++bb;
				++bi;
			}
		}

		std::vector<std::pair<size_t,size_t> > reconstruct(const std::vector<std::vector<entry> > &cache) {
			std::vector<std::pair<size_t,size_t> > res;
			size_t nb = cache.size()-1;
			if (nb > 0) {
				size_t na = cache[0].size()-1;
				if (cache[nb][na].sz > 0) {
					size_t di = cache[nb][na].sz-1;
					res.resize(di+1);
					while (na > 0 && nb > 0) {
						const entry &e = cache[nb][na];
						res[di] = std::pair<size_t,size_t>(e.a-1, e.b-1);
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

		template<typename IT> size_t lcs_sz_only(const IT &ahead, const IT &aend,
												 const IT &bhead, const IT &bend,
												 std::vector<std::vector<size_t> > &cache) {
			IT bb(bhead);
			size_t bi = 1;
			while (bb != bend) {
				size_t ai = 1;
				for (IT a(ahead); a != aend; ++a) {
					if (*a == *bb) {
						cache[bi][ai] = cache[bi^1][ai-1]+1;
					} else {
						if (cache[bi][ai-1] > cache[bi^1][ai])
							cache[bi][ai] = cache[bi][ai-1];
						else
							cache[bi][ai] = cache[bi^1][ai];
					}
					++ai;
				}
				++bb;
				bi ^= 1;
			}
			return cache[bi^1][cache[bi^1].size()-1];
		}

	}

	using namespace details;

	/* dst must be the back_inserter into the Container of std::pair<size_t, size_t> */
	template<typename IT, typename OIT>
	size_t lcs(const IT &ahead, const IT &aend,
			   const IT &bhead, const IT &bend,
			   OIT dst)
	{
		size_t a_sz = getsize(ahead, aend, typename std::iterator_traits<IT>::iterator_category());
		size_t b_sz = getsize(bhead, bend, typename std::iterator_traits<IT>::iterator_category());
		std::vector<std::vector<entry> > cache(b_sz+1, std::vector<entry>(a_sz+1));
		lcs_r(ahead, aend, bhead, bend, cache);
		std::vector<std::pair<size_t,size_t> > res(reconstruct(cache));
		std::copy(res.begin(), res.end(), dst);
		return res.size();
	}

	/* size-optimized version if you need only the size, but don't need the actual correspondence */
	template<typename IT>
	size_t lcs(const IT &ahead, const IT &aend,
			   const IT &bhead, const IT &bend)
	{
		size_t a_sz = getsize(ahead, aend, typename std::iterator_traits<IT>::iterator_category());
		size_t b_sz = getsize(bhead, bend, typename std::iterator_traits<IT>::iterator_category());
		if (a_sz <= b_sz) {
			std::vector<std::vector<size_t> > cache(2, std::vector<size_t>(a_sz+1, 0));
			return lcs_sz_only(ahead, aend, bhead, bend, cache);
		} else {
			std::vector<std::vector<size_t> > cache(2, std::vector<size_t>(b_sz+1, 0));
			return lcs_sz_only(bhead, bend, ahead, aend, cache);
		}
	}
}
