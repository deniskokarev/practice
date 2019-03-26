#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <unistd.h>
#include <getopt.h>
#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <set>
#include <random>
#include <sstream>
#include "ilog.hpp"

#define dim(X)	((sizeof(X)/sizeof(X[0])))

static void die(const char *fmt, ...) {
	va_list argp;
	int save_err = errno;
	
	fprintf(stderr, "rkmatch: ");
	va_start(argp, fmt);
	vfprintf(stderr, fmt, argp);
	va_end(argp);
	if (save_err)
		fprintf(stderr, "; perror: %s", strerror(save_err));
	fprintf(stderr, "\n");
	exit(1);
}

static void usage(char *cmd) {
	printf("Perform Rabin-Karp string matching\n");
	printf("@author Denis Kokarev\n");
	printf("Usage:\n");
	printf("\t%s <patterns.txt>\n", cmd);
	printf("<patterns.txt> list of desired strings to match");
	printf("input data for filtering is supplied on stdin\n");
	printf("output will have lines that match at least one pattern string\n");
}

// load input strings into correspondent log2(len) bucket
// and assign 1-based id to each
std::vector<std::vector<std::pair<std::string,int>>> load_patterns(std::istream &is) {
	std::vector<std::vector<std::pair<std::string,int>>> spat;
	int id = 1;
	std::string s;
	while (std::getline(is, s)) {
		int slen = int(s.length());
		int slen_l2 = ilog<2>(slen+1)-1; // floor(log2(slen));
		if (spat.size() <= slen_l2)
			spat.resize(slen_l2+1);
		spat[slen_l2].push_back(std::make_pair(s, id++));
	}
	return spat;
}

struct STR_PFX_SFX {
	int id;
	int ofs;
	std::string str;
	std::string pfx, sfx;
};

// make sure that we have only one pfx per sfx
std::vector<std::vector<STR_PFX_SFX>> build_pfx_sfx(const std::vector<std::vector<std::pair<std::string,int>>> &spat) {
	std::vector<std::vector<STR_PFX_SFX>> ps(spat.size());
	for (int l2=0; l2<spat.size(); l2++) {
		const auto &sv = spat[l2];
		const int slen = 1<<l2;
		std::map<std::string, std::pair<std::string, std::string>> uniq; // sfx -> (pfx,str)
		for (auto &s_id:sv) {
			const std::string &s = s_id.first;
			const std::string pfx = s.substr(0, slen);
			const std::string sfx = s.substr(s.length()-slen, slen);
			const auto fnd = uniq.find(sfx);
			if (fnd != uniq.end())
				die("Pattern conflict between '%s' and '%s'. Different prefixes: '%s'/'%s' are not allowed for suffix '%s'", fnd->second.second.c_str(), s.c_str(), fnd->second.first.c_str(), pfx.c_str(), sfx.c_str());
			uniq[sfx] = std::make_pair(pfx, s);
			int ofs = int(s.length()) - slen;
			ps[l2].push_back(STR_PFX_SFX {s_id.second, ofs, s, pfx, sfx});
		}
	}
	return ps;
}

static unsigned hash(const std::string &s, unsigned mod_mask, unsigned base) {
	uint64_t h = 0;
	for (unsigned char c:s) {
		h *= base;
		h += c;
		h &= mod_mask;
	}
	return unsigned(h);
}

struct BM {
	unsigned base;
	unsigned mod;
};

static const unsigned primes[] = {
	3,   5,   7,  11,  13,  17,  19,  23,  29,  31,
	37,  41,  43,  47,  53,  59,  61,  67,  71,  73,
	79,  83,  89,  97, 101, 103, 107, 109, 113, 127,
	131, 137, 139, 149, 151, 157, 163, 167, 173, 179,
	181, 191, 193, 197, 199, 211, 223, 227, 229, 233,
	239, 241, 251, 257, 263, 269, 271, 277, 281, 283,
	293, 307, 311, 313, 317, 331, 337, 347, 349, 353,
	359, 367, 373, 379, 383, 389, 397, 401, 409, 419,
	421, 431, 433, 439, 443, 449, 457, 461, 463, 467,
	479, 487, 491, 499, 503, 509, 521, 523, 541, 547
};

// resolve smallest mod that gives us no hash collisions
std::vector<BM> find_min_mod_base(const std::vector<std::vector<STR_PFX_SFX>> &ps) {
	std::vector<BM> bm(ps.size());
	for (int l2=0; l2<ps.size(); l2++) {
		if (ps[l2].size() == 0)
			continue;
		std::set<std::string> uniq_s;
		for (auto &sps:ps[l2]) {
			uniq_s.insert(sps.pfx);
			uniq_s.insert(sps.sfx);
		}
		unsigned mod = 1U << (ilog<2>(uniq_s.size())); // 1 << ceil(log2(uniq_s.size()))
		constexpr unsigned MX = 1U << 31;
		unsigned base = 0;
		while (mod < MX) {
			unsigned mod_mask = mod-1;
			for (auto pr:primes) {
				std::set<unsigned> uniq_h;
				bool is_uniq = true;
				for (auto &s:uniq_s) {
					unsigned h = hash(s, mod_mask, pr);
					auto fnd = uniq_h.find(h);
					is_uniq &= (fnd == uniq_h.end());
					uniq_h.insert(h);
				}
				if (is_uniq && *uniq_h.begin() != 0) {
					// we don't want hashcodes falling on 0
					base = pr;
					goto end_mods_primes;
				}
			}
			mod *= 2;
		}
	end_mods_primes:
		if (base == 0)
			die("Could not find base/mod to build unique hash table");
		else
			bm[l2] = BM {base, mod};
	}
	return bm;
}

constexpr int EXHN = 4;

// element of hash table
struct HEL {
	// if there was prefix match ofs back then
	// we identified pattern id
	int id;
	int ofs;
	unsigned hpfx;
	unsigned exhash[EXHN];
};

constexpr int RK_SIGNATURE = 12345;
constexpr int RK_VER = 1;

// hash tables segment for patterns len [2^n, 2^(n+1))
// the expectation is sizeof(HSEG) >= sizeof(HEL)
struct HSEG {
	size_t seg_sz;
	unsigned base;
	unsigned mod;
	unsigned exbase[EXHN];
	HEL hel[];
};

static size_t hseg_size(int m) {
	return (sizeof(HSEG) + sizeof(HEL)*m + sizeof(HSEG)-1)/sizeof(HSEG);
}

void fill_rnd_base(unsigned *exbase, int seed, unsigned base) {
	// pick other EXHN uniq hash bases randomly
	std::mt19937 rnd(seed);
	std::set<unsigned> uniq_base;
	while (uniq_base.size() < EXHN) {
		unsigned rb = rnd() % dim(primes);
		if (primes[rb] != base)
			uniq_base.insert(primes[rb]);
	}
	int i = 0;
	for (unsigned eb:uniq_base) {
		exbase[i] = eb;
		i++;
	}
}

const void *build_hseg(std::vector<HSEG> &arena, const std::vector<std::vector<STR_PFX_SFX>> &ps, const std::vector<BM> &bm) {
	size_t tot_nel = 2;
	for (int l2=0; l2<ps.size(); l2++)
		tot_nel += hseg_size(bm[l2].mod);
	arena = std::vector<HSEG>(tot_nel);
	memset(arena.data(), 0, tot_nel*sizeof(HSEG));
	arena[0].seg_sz = hseg_size(0) * sizeof(HSEG);
	arena[0].base = RK_SIGNATURE;
	arena[0].mod = RK_VER;
	tot_nel = 1;
	for (int l2=0; l2<ps.size(); l2++) {
		const unsigned base = bm[l2].base;
		const unsigned mod = bm[l2].mod;
		const unsigned mod_mask = mod-1;
		HSEG &hs = arena[tot_nel];
		hs.seg_sz = hseg_size(mod) * sizeof(HSEG);
		hs.base = base;
		hs.mod = mod;
		tot_nel += hseg_size(mod);
		if (ps[l2].size() > 0) {
			// set hash bases randomly
			fill_rnd_base(hs.exbase, base+l2, base);
			// compute hashes for prefixes
			for (const STR_PFX_SFX &sps:ps[l2]) {
				unsigned h = hash(sps.pfx, mod_mask, base);
				HEL &hel = hs.hel[h];
				hel.id = -1;
				hel.ofs = -1;
				hel.hpfx = -1;
				for (int i=0; i<EXHN; i++)
					hel.exhash[i] = hash(sps.pfx, -1, hs.exbase[i]);
			}
			// for suffixes (some may match pfx)
			for (const STR_PFX_SFX &sps:ps[l2]) {
				unsigned h = hash(sps.sfx, mod_mask, base);
				HEL &hel = hs.hel[h];
				hel.id = sps.id;
				hel.ofs = sps.ofs;
				hel.hpfx = hash(sps.pfx, mod_mask, base);
				for (int i=0; i<EXHN; i++)
					hel.exhash[i] = hash(sps.sfx, -1, hs.exbase[i]);
			}
		}
	}
	HSEG &hs = arena[tot_nel];
	hs.base = -1;
	hs.mod = -1;
	return arena.data();
}

void dbg_prn_hseg(const void *data, FILE *fout) {
	char *cseg = (char*)data;
	HSEG *hseg = (HSEG*)cseg;
	cseg += hseg->seg_sz;
	fprintf(fout, "signature(%d)\n", hseg->base);
	fprintf(fout, "version(%d)\n", hseg->mod);
	int l2 = 0;
	hseg = (HSEG*)cseg;
	while (hseg->mod != -1) {
		cseg += hseg->seg_sz;
		fprintf(fout, "l2(%d)\n", l2);
		fprintf(fout, "base(%d)\n", hseg->base);
		fprintf(fout, "mod(%d)\n", hseg->mod);
		fprintf(fout, "exbase%d(%d)", 0, hseg->base);
		for (int i=1; i<EXHN; i++)
			fprintf(fout, ", exbase%d(%d)", i, hseg->exbase[i]);
		fprintf(fout, "\n");
		HEL *hel = hseg->hel;
		for (int i=0; i<hseg->mod; i++) {
			fprintf(fout, "%08d: id=%d, ofs=%d", i, hel[i].id, hel[i].ofs);
			for (int j=0; j<EXHN; j++)
				fprintf(fout, ", exhash%d=%d", j, hel[i].exhash[j]);
			fprintf(fout, "\n");
		}
		l2++;
		hseg = (HSEG*)cseg;
	}
}

int main(int argc, char **argv) {
	int verbose = 0;
	int debug = 0;
	char c;
	opterr = 0;
	while ((c = getopt(argc, argv, "vhg")) != -1) {
		switch (c) {
			case 'v':
				verbose = 1;
				break;
			case 'g':
				debug = 1;
				break;
			case 'h':
				usage(argv[0]);
				return(0);
			default:
				die("unknown cmd line argument");
		}
	}
#if 1
	if (argc-optind < 1)
		die("patterns.txt file is expected, see `%s -h` for more info", argv[0]);
	std::ifstream is_patterns(argv[1]);
	if (!is_patterns)
		die("Cannot open patterns file: %s", argv[1]);
#else
	std::stringstream is_patterns("z\nzz\nyyy\nyyyy\n");
#endif
	const auto spat = load_patterns(is_patterns);
	const auto ps = build_pfx_sfx(spat);
	const auto bm = find_min_mod_base(ps);
	std::vector<HSEG> arena;
	const void *data = build_hseg(arena, ps, bm);
	dbg_prn_hseg(data, stderr);
	return 0;
}
