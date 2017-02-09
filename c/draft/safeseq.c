/*
 * Build a short(est) continues sequence of numbers to cover all 10^4 safe codes
 * Since the optimal solution cannot be easily found (and awfully resembles
 * knapsack problem) we'll use greedy search approach
 */
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <stdlib.h>
#include <getopt.h>

/* sliding window of digits */
typedef struct {
	int sum;
	int dec_max;	/* max/10 */
} WRING;

/* get current window number before we're about to append another digit */
int win_sum_but_last(const WRING *win) {
	int sum = win->sum;
	sum %= win->dec_max;
	sum *= 10;
	return sum;
}

/* output a digit and shift the window */
int output_one_digit(int d, WRING *win) {
	int sum = win_sum_but_last(win);
	fputc('0'+d, stdout);
	win->sum = sum+d;
	return win->sum;
}	

/*
 * see which digit append is the most promising 
 * return the number we will cover by choosing this digit
 * dig - chosen digit
 * score - the "score" of the chosen digit
 * 	the score is the number of times the resulting number
 *  has been covered so far
 */
int best_next_digit(const WRING *win, const int *all_codes, int *dig, int *score) {
	int best_dig = 0, best_score = INT_MAX;
	int sum = win_sum_but_last(win);
	int d;
	for (d=0; d<10; d++) {
		if (all_codes[sum+d] < best_score) {
			best_score = all_codes[sum+d];
			best_dig = d;
		}
	}
	*score = best_score;
	*dig = best_dig;
	return sum+best_dig;
}

/* start printing next batch */
/* n < pow(10, wsz) */
void begin_next_batch(int n, int *all_codes, WRING *win, int wsz) {
	char rev[wsz];
	int d = n;
	int i;
	for (i=0; i<wsz; i++) {
		rev[i] = d%10;
		d /= 10;
	}
	for (i=wsz-1; i>=0; i--) {
		int n = output_one_digit(rev[i], win);
		all_codes[n]++;
	} 
}

/* generate the digits sequence to cover pow(10, wsz) numbers */
void generate(int wsz) {
	/* to count how many times we've covered each number */
	int all_codes_sz = 1;
	int i;
	for (i=0; i<wsz; i++)
		all_codes_sz *= 10;
	int *all_codes = (int*)calloc(sizeof(int), all_codes_sz);
	/* current sliding window */
	WRING win = {.sum = 0, .dec_max = all_codes_sz/10};
	/* covering all_codes[] while trying to "walk" digit by digit from each of them */
	for (i=0; i<all_codes_sz; i++) { 
		if (!all_codes[i]) {
			begin_next_batch(i, all_codes, &win, wsz);
			int dig, score, num;
			for (num = best_next_digit(&win, all_codes, &dig, &score);
				 !score;
				 num = best_next_digit(&win, all_codes, &dig, &score))
			{
				output_one_digit(dig, &win);
				all_codes[num]++;
			}
		}
	}
	fputc('\n', stdout);
	free(all_codes);
}

/* confirm that the digits sequence covers all pow(10, wsz) numbers */
int validate(int wsz) {
	/* to count how many times we've covered each number */
	int all_codes_sz = 1;
	int i;
	for (i=0; i<wsz; i++)
		all_codes_sz *= 10;
	int *all_codes = (int*)calloc(sizeof(int), all_codes_sz);
	int c;
	int num = 0;
	for (i=0; i<wsz; i++) {
		if ((c=fgetc(stdin))>=0 && isdigit(c)) {
			num %= all_codes_sz/10;
			num *= 10;
			num += c-'0';
		} else {
			fprintf(stderr, "too short input");
		}
	}
	all_codes[num]++;
	while((c=fgetc(stdin))>=0 && isdigit(c)) {
		num %= all_codes_sz/10;
		num *= 10;
		num += c-'0';
		all_codes[num]++;
	}
	/* check correctness and efficiency */
	int over = 0;
	int rc = 0;
	for (i=0; i<all_codes_sz; i++) {
		if (!all_codes[i]) {
			fprintf(stderr, "number %d is not covered\n", i);
			rc = -1;
		} else {
			over += all_codes[i]-1;
		}
	}
	fprintf(stderr, "overcovered %d numbers\n", over);
	free(all_codes);
	return rc;
}

void usage(char *cmd) {
	fprintf(stdout,
			"Build a short(est) continues sequence of numbers to cover all 10^4 safe codes\n"
			"Since the optimal solution cannot be easily found (and awfully resembles\n"
			"knapsack problem) we'll use greedy search approach\n"
			"\tUsage:\n"
			"%s [-w <sz>] [-v]\n"
			"-w <sz> - safe code width, default 4\n"
			"-v - validate the given sequence, default - generate the sequence\n"
			"\tExample:\n"
			"%s -w3 | tee output | %s -w3 -v\n", cmd, cmd, cmd);
}

int main(int argc, char **argv) {
	int c;
	char mode = 'g';
	int wsz = 4;
	opterr = 0;
	while ((c = getopt(argc, argv, "w:vh")) != -1 ) {
		switch(c) {
		case 'w':
			wsz = atoi(optarg);
			if (wsz <= 0) {
				fprintf(stderr, "the width has to be > 0\n");
				return 1;
			} else if (wsz > 8) {
				fprintf(stderr, "you don't want width > 8\n");
				return 1;
			}
			break;
		case 'v':
			mode = 'v';
			break;
		case 'h':
		default:
			usage(argv[0]);
			return 1;
		}
	}
	if (mode == 'g') {
		generate(wsz);
		return 0;
	} else {
		return validate(wsz);
	}
}
