/**
 * A command-line tool to compile Aho-Corasic matching automata
 * @author Denis Kokarev
 * @see usage() for more info
 * use -std=c++11 for compilation
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <queue>
#include <vector>
#include "act.h"

struct ACT_NODE_COMP {
	unsigned next[1<<ACT_PAGE_P2] {0};
	unsigned sufref {0};
	int val {0};
	unsigned parent {0};
	char end {0};
	unsigned char ch {0};
};

void act_insert(std::vector<ACT_NODE_COMP> &nodes, const unsigned char *s, unsigned s_sz, int val) {
	unsigned root = ACT_ROOT;
	while (s_sz--) {
		unsigned bmask = *s++;
		for (int i=0; i<8/ACT_PAGE_P2; i++,bmask>>=ACT_PAGE_P2) {
			unsigned char bch = bmask & ((1<<ACT_PAGE_P2)-1);
			unsigned nroot = nodes[root].next[bch];
			if (nroot == 0) {
				nroot = int(nodes.size());
				nodes.resize(nodes.size()+1); // will call node constructor
				nodes[nroot].ch = bch;
				nodes[nroot].parent = root;
				nodes[root].next[bch] = nroot;
			}
			root = nroot;
		}
	}
	nodes[root].val = val;
	nodes[root].end = 1;
}

void act_build_sufref(std::vector<ACT_NODE_COMP> &nodes) {
	std::queue<unsigned> qq;
	// init root and its immediate children
	// start BFS on grandchildren
	nodes[ACT_ROOT].sufref = ACT_ROOT;
	for (unsigned next:nodes[ACT_ROOT].next) {
		if (next) {
			nodes[next].sufref = ACT_ROOT;
			for (unsigned nn:nodes[next].next)
				if (nn)
					qq.push(nn);
		}
	}
	while (!qq.empty()) {
		unsigned root = qq.front();
		qq.pop();
		unsigned char ch = nodes[root].ch;
		unsigned psf = nodes[nodes[root].parent].sufref;
		while (psf != ACT_ROOT && nodes[psf].next[ch] == 0)
			psf = nodes[psf].sufref;
		if (nodes[psf].next[ch] != 0)
			nodes[root].sufref = nodes[psf].next[ch];
		else
			nodes[root].sufref = ACT_ROOT; // couldn't find suffix
		for (unsigned next:nodes[root].next)
			if (next)
				qq.push(next);
	}
}

void act_fill_all_next(std::vector<ACT_NODE_COMP> &nodes) {
	std::queue<unsigned> qq;
	qq.push(ACT_ROOT);
	while (!qq.empty()) {
		unsigned root = qq.front();
		qq.pop();
		for (unsigned next:nodes[root].next)
			if (next)
				qq.push(next);
		for (unsigned ch=0; ch<(1<<ACT_PAGE_P2); ch++) {
			if (nodes[root].next[ch] == 0) {
				unsigned sr = nodes[root].sufref;
				if (nodes[sr].next[ch])
					nodes[root].next[ch] = nodes[sr].next[ch];
				else
					nodes[root].next[ch] = ACT_ROOT;
			}
		}
	}
}

void act_build_direct_sufref(std::vector<ACT_NODE_COMP> &nodes) {
	std::vector<char> seen(nodes.size(), 0);
	std::queue<unsigned> qq;
	qq.push(ACT_ROOT);
	seen[ACT_ROOT] = 1;
	while (!qq.empty()) {
		unsigned root = qq.front();
		qq.pop();
		if (root != ACT_ROOT && nodes[root].parent != ACT_ROOT) {
			if (!nodes[nodes[root].sufref].end)
				nodes[root].sufref = nodes[nodes[root].sufref].sufref;
		}
		for (unsigned next:nodes[root].next)
			if (next && !seen[next])
				qq.push(next), seen[next] = 1;
	}
}

static void die(const char *fmt, ...) {
	va_list argp;
	int save_err = errno;

	fprintf(stderr, "actcomp: ");
	va_start(argp, fmt);
	vfprintf(stderr, fmt, argp);
	va_end(argp);
	if (save_err)
		fprintf(stderr, "; perror: %s", strerror(save_err));
	fprintf(stderr, "\n");
	exit(1);
}

static void usage(char *cmd) {
	printf("Compile Aho-Corasic matching automata\n");
	printf("@author Denis Kokarev, at&t\n");
	printf("Usage:\n");
	printf("\t%s <patterns.txt> <patterns.bin>\n", cmd);
	printf("<patterns.txt> - input - each line has a pattern and 31-bit integer value separated by |\n");
	printf("<patterns.bin> - output - binary image for matching automata,\n");
	printf("patterns.bin output size will be about %d times the size of patterns.txt\n", 8*int(sizeof(ACT_NODE))/ACT_PAGE_P2);
}

int main(int argc, char **argv) {
	int c;
	int debug = 0;
	int verbose = 0;
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
	if (argc-optind < 2)
		die("patterns.txt and patterns.bin files expected, see `%s -h` for more info", argv[0]);
	std::vector<ACT_NODE_COMP> nodes(2);
	char *fpatnm = argv[optind];
	FILE *fpat = fopen(fpatnm, "r");
	if (!fpat)
		die("couldn't open %s pattern file for reading", fpatnm);
	char s[1024];
	std::vector<std::string> vpat;
	unsigned line = 0;
	if (verbose)
		fprintf(stderr, "start compiling %s...\n", fpatnm);
	while (fgets(s, sizeof(s), fpat)) {
		line++;
		int s_sz = int(strlen(s));
		if (s[s_sz-1] != '\n')
			die("Input patterns should be no longer than %d\n", (int)sizeof(s));
		s_sz--;
		int val = line-1; // default value is 0-based line number
		for (int i=s_sz-1; i>=0; i--) {
			if (s[i] == '|') {
				s_sz = i;
				val = atoi(s+i+1);
				break;
			}
		}
		act_insert(nodes, (const unsigned char*)s, s_sz, val);
		s[s_sz] = 0;
		vpat.push_back(s);
	}
	fclose(fpat);
	act_build_sufref(nodes);
	act_fill_all_next(nodes);
	act_build_direct_sufref(nodes);
	if (verbose)
		fprintf(stderr, "done compiling\n");
	char *fbinnm = argv[optind+1];
	if (verbose)
		fprintf(stderr, "saving into %s...\n", fbinnm);
	FILE *fbin = fopen(fbinnm, "w");
	if (!fbin)
		die("cannot open binary output file %s for writing", fbinnm);
	nodes[0].val = ACT_FILE_SIGNATURE;
	for (const auto &cn:nodes) {
		ACT_NODE save;
		save.sufref = cn.sufref;
		save.val = cn.val;
		save.end = cn.end;
		memcpy(save.next, cn.next, sizeof(cn.next));
		size_t rc = fwrite(&save, 1, sizeof(save), fbin);
		if (rc != sizeof(save))
			die("write error");
	}
	fclose(fbin);
	if (verbose)
		fprintf(stderr, "done saving\n");
	if (debug) {
		if (verbose)
			fprintf(stderr, "ready for search:\n");
		unsigned n = ACT_ROOT;
		int c;
		while ((c=fgetc(stdin)) != EOF) {
			unsigned bmask = c;
			for (int i=0; i<8/ACT_PAGE_P2; i++,bmask>>=ACT_PAGE_P2)
				n = nodes[n].next[bmask & ((1<<ACT_PAGE_P2)-1)];
			for (unsigned en=n; en != ACT_ROOT; en=nodes[en].sufref) {
				if (nodes[en].end) {
					int val = nodes[en].val;
					if (verbose && val >=0 && val<(int)vpat.size())
						fputc('"', stdout), fwrite(vpat[val].c_str(), 1, vpat[val].size(), stdout), fputc('"', stdout);
					else
						fprintf(stdout, "%d ", val);
					fputc(' ', stdout);
				}
			}
			if (c == '\n')
				fputc('\n', stdout);
		}
	}
	return 0;
}
