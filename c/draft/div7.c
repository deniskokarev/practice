#include <stdio.h>
#include <inttypes.h>

uint64_t tryCard(int sum, int me) {
	if (me < 0)
		return 0;
	if (sum == me) {
		return 5;
	} else if (sum > me) {
		uint64_t rc = tryCard(sum-me, me);
		return tryCard(sum, me-1) + rc;
	} else {
		return tryCard(sum, me-1);
	}
}

int main(int argc, char **argv) {
	fprintf(stdout, "%" PRIu64 "\n", tryCard(2, 1));
}
