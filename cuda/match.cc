/*
 * match 8 sequentially ascending chars in large text
 */
#include <vector>
#include <stdio.h>
#include <stdlib.h>

constexpr int STREAMS = 23; // 16K
constexpr int STRSZ = 121; // 16K long
constexpr char NL = '\n';
constexpr char SFILL = ' ';


char buf[STREAMS+1][STRSZ];

void die(const char *err) {
	fprintf(stderr, "%s\n", err);
	exit(1);
}

int main(int argc, char **argv) {
	int rc;
	int over = 0;
	while (!feof(stdin)) {
		size_t sz = STRSZ-over;
		char *s = buf[0];
		memcpy(s, buf[STREAMS], over);
		int nstreams;
		for (nstreams=0; nstreams < STREAMS && (rc=fread(s+over, 1, sz, stdin)) > 0; nstreams++,s+=STRSZ) {
			if (rc == sz) {
				int i;
				for (i=STRSZ-1; i>0 && s[i] != NL; i--);
				if (i==0)
					die("Cannot use strings greater than 16K");
				over = STRSZ-i-1;
				memcpy(s+STRSZ, s+i+1, over);
				memset(s+i, SFILL, over);
				s[STRSZ-1] = '\n';
			} else {
				memset(s+over+rc, SFILL, STRSZ-over-rc);
				over = 0;
				break;
			}
			sz = STRSZ-over;
		}
		if (nstreams < STREAMS) {
			memset(buf[nstreams+1], SFILL, (STREAMS-nstreams-1)*STRSZ-1); // fill up
			buf[STREAMS-1][STRSZ-1] = '\n';
		}
		fwrite(buf, 1, STREAMS*STRSZ, stdout);
	}
}
