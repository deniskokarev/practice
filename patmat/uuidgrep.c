/**
 * extract all UUIDs in the input stream
 * @author Denis Kokarev
 */
#include "uuidmatch.h"

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

	fprintf(stderr, "uuidgrep: ");
	va_start(argp, fmt);
	vfprintf(stderr, fmt, argp);
	va_end(argp);
	if (save_err)
		fprintf(stderr, "; perror: %s", strerror(save_err));
	fprintf(stderr, "\n");
	exit(1);
}

static void usage(char *cmd) {
	printf("Extract all UUIDs detected in the input stream\n");
	printf("@author Denis Kokarev\n");
	printf("Usage:\n");
	printf("\t%s <input.txt >uuid.txt\n", cmd);
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
	UMSTATE umstate;
	um_init(&umstate);
#ifdef DEBUG
	const int bufsz = UMPATLEN;
#else
	const int bufsz = 1<<14;
#endif
	char buf[2][bufsz];
	int rbuf = 0;
	size_t sz;
	while ((sz=fread(&buf[rbuf], 1, sizeof(buf[0]), stdin))>0) {
		for (int i=0; i<sz; i++) {
			if (um_match(&umstate, buf[rbuf][i])) {
				if (i>=UMPATLEN-1) {
					fwrite(&buf[rbuf][i-UMPATLEN+1], 1, UMPATLEN, stdout);
				} else {
					fwrite(&buf[rbuf^1][bufsz-UMPATLEN+i+1], 1, UMPATLEN-1-i, stdout);
					fwrite(&buf[rbuf][0], 1, i+1, stdout);
				}
				fputc('\n', stdout);
			}
		}
		rbuf ^= 1;
	}
}
