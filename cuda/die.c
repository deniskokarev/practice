#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>

void die(const char *fmt, ...) {
	va_list argp;
	int save_err = errno;

	va_start(argp, fmt);
	vfprintf(stderr, fmt, argp);
	va_end(argp);
	if (save_err)
		fprintf(stderr, "; perror: %s", strerror(save_err));
	fprintf(stderr, "\n");
	exit(1);
}
