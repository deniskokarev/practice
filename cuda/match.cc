/*
 * match 8 sequentially ascending chars in large text
 */
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <errno.h>
#include "die.h"
#include "transpose.hh"

constexpr int STREAMS = 128; // 16K
constexpr int STRSZ = STREAMS;
constexpr char NL = '\n';
constexpr char SFILL = ' ';

char ibuf[STREAMS+1][STRSZ];
char obuf[STRSZ][STREAMS];

int main(int argc, char **argv) {
	int rc;
	int over = 0;
	Match::CudaTranspose transpose;

	if ((rc=transpose.init((char*)ibuf, (char*)obuf, STRSZ))!=0)
		die("CudaTranspose initialization error");
	while (!feof(stdin)) {
		size_t sz = STRSZ-over;
		char *s = ibuf[0];
		memcpy(s, ibuf[STREAMS], over);
		int nstreams;
		for (nstreams=0; nstreams < STREAMS && (rc=fread(s+over, 1, sz, stdin)) > 0; nstreams++,s+=STRSZ) {
			if (rc == sz) {
				int i;
				for (i=STRSZ-1; i>0 && s[i] != NL; i--);
				if (i==0)
					die("Cannot use strings greater than %d", STRSZ);
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
		if (nstreams < STREAMS)
			memset(ibuf[nstreams+1], SFILL, (STREAMS-nstreams-1)*STRSZ); // fill up
		//fwrite(ibuf, 1, STREAMS*STRSZ, stdout);
		transpose.run();
		fwrite(obuf, 1, STREAMS*STRSZ, stdout);
	}
}
