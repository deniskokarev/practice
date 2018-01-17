/* ACMP 509 */
#include <iostream>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <cassert>
#include <cstring>

constexpr int NROW = 2;
constexpr int NCOL = 4;

struct P {
	int x, y;
	P operator+(const P &b) const {
		return P {x+b.x, y+b.y};
	}
	operator bool() const {
		return x>=0 && x<NCOL && y>=0 && y<NROW;
	}
};

const P moves[] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

struct B {
	int dist;	// moves made so far
	P pos;		// where is #
	char brd[NROW][NCOL];
	uint64_t hash() const {
		return *(uint64_t*)brd; // taking advantage of board size fitting 8 bytes
	}
	bool operator==(const B &b) const {
		return ::memcmp(brd, b.brd, sizeof(brd)) == 0;
	}
	bool make_move(const P &dir) {
		P np = pos+dir;
		if (np) {
			std::swap(brd[pos.y][pos.x], brd[np.y][np.x]);
			pos = np;
			dist++;
			return true;
		} else {
			return false;
		}
	}
};

std::istream &operator>>(std::istream &is, B &b) {
	b.dist = 0;
	for (int i=0; i<NROW; i++) {
		std::string s;
		is >> s;
		assert(s.length() == NCOL);
		for (int j=0; j<NCOL; j++) {
			b.brd[i][j] = s[j];
			if (s[j] == '#') {
				b.pos.x = j;
				b.pos.y = i;
			}
		}
	}
	return is;
}

struct BHasher {
	size_t operator()(const B &b) const {
		return b.hash();
	}
};

int main(int argc, char **argv) {
	B start, end;
	std::cin >> start >> end;
	std::queue<B> qq;
	qq.push(start);
	std::unordered_multiset<B, BHasher> seen;
	seen.reserve(2*3*4*5*6*7*8 * 4);
	seen.insert(start);
	int ans = -1;
	while (qq.size() > 0) {
		const B &b = qq.front();
		if (b == end) {
			ans = b.dist;
			break;
		}
		for (auto &m:moves) {
			B nb = b;
			if (nb.make_move(m) && seen.find(nb) == seen.end()) {
				qq.push(nb);
				seen.insert(nb);
			}
		}
		qq.pop();
	}
	std::cout << ans << std::endl;
	return 0;
}
