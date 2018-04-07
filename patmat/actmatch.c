#include "act.h"
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>

const static char usage[] = "simple test-tool to match the input stream against precompiled patterns and print the values detected\n";

static void die(const char *fmt, ...) {
	va_list argp;
	int save_err = errno;

	fprintf(stderr, "actmatch: ");
	va_start(argp, fmt);
	vfprintf(stderr, fmt, argp);
	va_end(argp);
	if (save_err)
		fprintf(stderr, "; perror: %s", strerror(save_err));
	fprintf(stderr, "\n");
	exit(1);
}

int main(int argc, char **argv) {
	if (argc < 2) {
		fprintf(stderr, usage);
		die("run as `%s patterns.bin <file`", argv[0]);
	}
	ACT act;
	int rc = act_attach_mmap(&act, argv[1]);
	if (rc != 0) {
		fprintf(stderr, usage);
		die("couldn't use specified patterns file %s, act_attach_mmap() error code %d", argv[1], rc);
	}
	/* consume input char-by-char */
	unsigned node = ACT_ROOT;
	int c;
	while ((c=fgetc(stdin)) >= 0) {
		node = act_next_char(act.nodes, node, (char)c);
		int val;
		for (unsigned result_node=node; act_next_match(act.nodes, &result_node, &val);)
			fprintf(stdout, "%d ", val);
		if (c == '\n')
			fprintf(stdout, "\n");
	}
	rc = act_detach_mmap(&act);
	if (rc != 0)
		die("act_detach_mmap() error code %d", rc);
}
