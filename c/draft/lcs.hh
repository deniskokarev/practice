/*
 * LCS - longest common subsequence
 */
#include <vector>
#include <stack>

namespace lcs {
	
	namespace details {
		
		struct cache_item {
			size_t sz;
			int na, nb;
			cache_item():sz(0),na(-1),nb(-1){}
			cache_item(int _sz, int _na, int _nb):sz(_sz),na(_na),nb(_nb){}
		};

		template <typename IT> struct rnode {
			IT a;
			IT b;
			const IT &aend;
			const IT &bend;
			int na;
			int nb;
			int ai;
			int bi;
			int cnt;
			int pfx;
			rnode(const IT &_a, int _ai, const IT &_aend,
					   const IT &_b, int _bi, const IT &_bend,
					   int _pfx):
				a(_a), b(_b), aend(_aend), bend(_bend), na(_ai), nb(_bi), ai(_ai), bi(_bi), cnt(0), pfx(_pfx) {
			}
			rnode(const rnode &si):
				a(si.a), b(si.b), aend(si.aend), bend(si.bend), na(si.ai), nb(si.bi), ai(si.ai), bi(si.bi), cnt(0), pfx(si.pfx) {
			}
			rnode next() {
				cnt++;
				switch(cnt) {
				case 1:
					return rnode(*this).advance_a();
				case 2:
					return rnode(*this).advance_b();
				default:
					return *this;
				}
			}
			rnode &advance_a() {
				++ai;
				++a;
				return *this;
			}
			rnode &advance_b() {
				++bi;
				++b;
				return *this;
			}
			rnode &inc() {
				pfx++;
				return *this;
			}
			bool end() {
				return cnt > 1;
			}
			bool bottom() {
				return a == aend || b == bend;
			}
		};

		template<typename IT> void lcs_r(const IT &ahead, const IT &aend, int ai,
										 const IT &bhead, const IT &bend, int bi,
										 std::vector<std::vector<cache_item> > &cache) {
			std::stack<rnode<IT>> stack;
			stack.push(rnode<IT>(ahead, 0, aend, bhead, 0, bend, 0));
			while (!stack.empty()) {
				auto s = stack.top();
				stack.pop();
				if (cache[s.ai][s.bi].na < 0) {
					if (s.bottom()) {
						cache[s.ai][s.bi].sz = s.pfx;
					} else if (*s.a == *s.b) {
						stack.push(s.inc().advance_a().advance_b());
					} else if (s.end()) {
						if (cache[s.ai+1][s.bi].sz > cache[s.ai][s.bi+1].sz)
							cache[s.ai][s.bi] = cache_item(cache[s.ai+1][s.bi].sz, s.ai+1, s.bi);
						else
							cache[s.ai][s.bi] = cache_item(cache[s.ai][s.bi+1].sz, s.ai, s.bi+1);
					} else {
						stack.push(s);
						stack.push(s.next());
					}
				}
			}
		}

		std::vector<std::pair<int,int> > reconstruct(const std::vector<std::vector<cache_item> > &cache) {
			std::vector<std::pair<int,int> > res;
			int na, nb;
			na = nb = 0;
			if (cache[na][nb].sz > 0) {
				while (na >= 0 && nb >= 0) {
					const cache_item &e = cache[na][nb];
					res.push_back(std::pair<int,int>(na, nb));
					na = e.na;
					nb = e.nb;
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
	
	template<typename IT> std::vector<std::pair<int,int> > lcs(const IT &ahead, const IT &aend, const IT &bhead, const IT &bend) {
		std::vector<std::vector<cache_item> > cache(getsize(ahead, aend, typename std::iterator_traits<IT>::iterator_category())+1, std::vector<cache_item>(getsize(bhead, bend, typename std::iterator_traits<IT>::iterator_category())+1));
		lcs_r(ahead, aend, 0, bhead, bend, 0, cache);
		return reconstruct(cache);
	}
}
