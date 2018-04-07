/**
 * a-la fgrep utility
 * grep input lines for match with any of precompiled patterns
 * @author Denis Kokarev
 */
#include "act.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>

static void die(const char *fmt, ...) {
	va_list argp;
	int save_err = errno;

	fprintf(stderr, "actfgrep: ");
	va_start(argp, fmt);
	vfprintf(stderr, fmt, argp);
	va_end(argp);
	if (save_err)
		fprintf(stderr, "; perror: %s", strerror(save_err));
	fprintf(stderr, "\n");
	exit(1);
}

static void usage(char *cmd) {
	printf("Match the input strings with actcomp precompiled automata,\n");
	printf("works similar to fgrep\n");
	printf("@author Denis Kokarev, at&t\n");
	printf("Usage:\n");
	printf("\t%s patterns.bin <input.txt >filtered.txt\n", cmd);
	printf("patterns.bin - precompiled patterns.txt file, see `actcomp -h`\n");
}

int main(int argc, char **argv) {
	int c;
	opterr = 0;
	while ((c = getopt(argc, argv, "h")) != -1) {
		switch (c) {
		case 'h':
			usage(argv[0]);
			return(0);
		default:
			die("unknown cmd line argument");
		}
	}
	if (argc-optind < 1) {
		usage(argv[0]);
		die("run as `%s patterns.bin <file`", argv[0]);
	}
	ACT act;
	int rc = act_attach_mmap(&act, argv[optind]);
	if (rc != 0)
		die("couldn't use specified patterns file %s, act_attach_mmap() error code %d", argv[optind], rc);
	/* store the lines in ring buffer */
	const unsigned bufsz = 1<<16; // 64K per line max
	const unsigned bufszmsk = bufsz-1;
	char buf[bufsz];
	int tail = 0;
	int lnbeg = 0;
	unsigned node = ACT_ROOT;
	while ((c=fgetc(stdin)) >= 0) {
		buf[tail++] = c;
		tail &= bufszmsk;
		if (c == '\n')
			lnbeg = tail;
		node = act_next_char(act.nodes, node, c);
		int val;
		unsigned result_node = node;
		/* if any pattern match occured */
		if (act_next_match(act.nodes, &result_node, &val)) {
			while ((c=fgetc(stdin)) >= 0 && c != '\n') {
				buf[tail++] = c;
				tail &= bufszmsk;
				if (tail == lnbeg)
					die("the input line exceeded %d bytes", bufsz);
			}
			if (lnbeg > tail) {
				fwrite(buf+lnbeg, 1, bufsz-lnbeg, stdout);
				fwrite(buf, 1, tail, stdout);
			} else {
				fwrite(buf+lnbeg, 1, tail-lnbeg, stdout);
			}
			fputc('\n', stdout);
			lnbeg = tail;
			node = ACT_ROOT;
		}
	}
	rc = act_detach_mmap(&act);
	if (rc != 0)
		die("act_detach_mmap() error code %d", rc);
}
