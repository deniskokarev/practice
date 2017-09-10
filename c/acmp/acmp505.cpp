/* ACMP 505 */
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

using SV = vector<short>;


unsigned int crc32b(const unsigned char *message, int sz) {
	int i, j;
	unsigned int byte, crc, mask;

	i = 0;
	crc = 0xFFFFFFFF;
	while (sz-- > 0) {
		byte = message[i];            // Get next byte.
		crc = crc ^ byte;
		for (j = 7; j >= 0; j--) {    // Do eight times.
			mask = -(crc & 1);
			crc = (crc >> 1) ^ (0xEDB88320 & mask);
		}
		i = i + 1;
	}
	return ~crc;
}

namespace std {
	template<> struct hash<SV> {
		size_t operator()(const SV &sv) const {
			return crc32b((const unsigned char*)&sv[0], sv.size()*sizeof(sv[0]));
		}
	};
};

int main(int argc, char **argv) {
	int l, m, n;
	cin >> l >> m >> n;
	unordered_map<SV, int> ttmap;
	for (int i=0; i<m; i++) {
		SV tt(l);
		int id;
		cin >> id;
		for (auto &t:tt)
			cin >> t;
		ttmap[tt] = id;
	}
	int ok=0, bad=0;
	for (int i=0; i<n; i++) {
		SV ss(l);
		for (auto &s:ss)
			cin >> s;
		auto fnd = ttmap.find(ss);
		if (fnd != ttmap.end()) {
			cout << fnd->second;
			ok++;
		} else {
			cout << '-';
			bad++;
		}
		cout << endl;
	}
	cout << "OK=" << ok << " BAD=" << bad << endl;
	return 0;
}
