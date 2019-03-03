#include <stdio.h>
/* Hackerrank https://www.hackerrank.com/challenges/reversi */

/** board size */
#define MAX_DIM			8

/**
 * @brief it is very convenient to encode opposite sides colors as opposite numbers
 */
typedef signed char CHIP_COLOR;

#define	COLOR_VACANT	((CHIP_COLOR)0)		/**< unoccupied space */
#define	COLOR_POS		((CHIP_COLOR)1)		/**< WHITE is convenient to encode as positive */
#define	COLOR_NEG		((CHIP_COLOR)-1)	/**< BLACK is convenient to encode as negative */

/**
 * @brief This is a Reversy game field 8x8 grid
 *
 * First dimension is X (column) second dimension is Y (row)
 */
typedef struct {
	CHIP_COLOR b[MAX_DIM][MAX_DIM];
} GAME_STATE;
	 
/**
 * @brief Every turn has X (column) and Y (row) coordinates and the color
 */
typedef struct tagGAME_TURN {
	CHIP_COLOR		color;
	signed char		x, y;
} GAME_TURN;

#define SAME_COLOR(A, B)		(A == B)
#define ALTER_COLOR(A)			(-(A))

#define E_OK		0
#define E_OCC		1
#define E_NO_OPP	2
#define E_NO_FLIPS	3
#define E_NO_TURNS	4

#define min(A,B) ((A<B) ? A : B)
#define max(A,B) ((A>B) ? A : B)
#define dim(X)	(sizeof(X)/sizeof(X[0]))

typedef struct {
	signed char x, y;
	signed char px, py;
} AXIS_ITERATOR;

typedef enum {
	AXIS_DIR_BACKWARD = -1,
	AXIS_DIR_FORWARD = 1
} AXIS_DIR;

static CHIP_COLOR *axis_iter_next(GAME_STATE *state, AXIS_ITERATOR *iter, AXIS_DIR dir) {
	iter->x += iter->px*dir;
	iter->y += iter->py*dir;
	if (iter->x >= 0 && iter->x < MAX_DIM && iter->y >= 0 && iter->y < MAX_DIM)
		return &state->b[iter->x][iter->y];
	else
		return 0;
}

/*
 * Flip over 1D array of chips.
 * Return number of captured ones.
 */
static char flip_row(GAME_STATE *state, AXIS_ITERATOR *iter, CHIP_COLOR target_color) {
	CHIP_COLOR	*pcolor;
	CHIP_COLOR opposite_color = ALTER_COLOR(target_color);
	char flip = 0;
	signed char n = 0;
	pcolor = axis_iter_next(state, iter, AXIS_DIR_BACKWARD);
	while (pcolor && *pcolor == opposite_color) {
		pcolor = axis_iter_next(state, iter, AXIS_DIR_BACKWARD);
		n++;
	}
	if (pcolor && *pcolor == target_color) {
		while (n>0) {
			pcolor = axis_iter_next(state, iter, AXIS_DIR_FORWARD);
			*pcolor = target_color;
			flip++;
			n--;
		}
	}
	return flip;
} 

/*
 * Scan and try to flip all axises relative to given 'turn'
 * Don't touch 'turn' field itself.
 * We make axis projection on 1D array and call flip_row()
 * for every axis.
 * Return number of captured chips. 
 */
static char flip_axises(GAME_STATE *state, const GAME_TURN *turn) {
	AXIS_ITERATOR i;
	char flip = 0;
	/* VERTIVAL, HORIZONTAL, DIAGONAL, CROSS-DIAGONAL in both directions */
	for (i.px = -1; i.px <= 1; i.px++) {
		for (i.py = -1; i.py <= 1; i.py++) {
			if (i.px | i.py) {	/* except direction 0,0 */
				i.x = turn->x;
				i.y = turn->y;
				flip += flip_row(state, &i, turn->color);
			}
		}
	}
	return flip;
}

/*
 * Make quick validation; sutable for automatic turn generation
 * returns. The final answer could be made only by flip_axises()
 * 1 - Yes
 * 0 - No
 */
static int quick_validate_turn(const GAME_STATE *state, const GAME_TURN *turn) {
	/* you cannot make a turn if this place is already occupied */
	return (state->b[turn->x][turn->y] == COLOR_VACANT);
}

/* 
 * Make turn on position 'state'.
 * Return amount of flip overs
 */
int make_turn(GAME_STATE *state, const GAME_TURN *turn) {
	char flip = 0;

	if (quick_validate_turn(state, turn)) {
		if ((flip = flip_axises(state, turn)) > 0) {
			/* if there is something to capture */
			state->b[turn->x][turn->y] = turn->color;
		}
	}
	return flip;
}


/*
 * Validate turn
 * Don't use it in automatic procedures, because of it is slow.
 * returns
 * E_OK - Ok
 * E_OCC - is already occupied
 * E_NO_FLIPS - no flips
 */
int validate_turn(const GAME_STATE *state, const GAME_TURN *turn) {
	GAME_STATE	tmp_state;
	int			e_code;

	if (!quick_validate_turn(state, turn)) {
		e_code = E_OCC;
	} else {
		/* Quick checking is OK */
		tmp_state = *state;
		if (! flip_axises(&tmp_state, turn)) {
			/* Slow flip_axises is ERR */
			e_code = E_NO_FLIPS;
		} else {
			e_code = E_OK;
		}
	}
	return e_code;
}

/*
 * Turns generator. Don't use it in solution search, because of it is slow.
 * Makes a list of possible turns in game position 'state' by color 'color'
 * returns 0 if no possible turns left
 */
int make_turn_list(GAME_TURN turn[MAX_DIM * MAX_DIM], const GAME_STATE *state, CHIP_COLOR color) {
	GAME_TURN	t;
	int			i = 0;

	t.color = color;
	for (t.x = 0; t.x < MAX_DIM; t.x++) {
		for (t.y = 0; t.y < MAX_DIM; t.y++) {
			if (! validate_turn(state, &t)) {
				turn[i++] = t;
			}
		}
	}
	return i;
}

/*
 * Account chips of certain color on position 'state'
 */
int chips_count(const GAME_STATE *state, CHIP_COLOR color) {
	char	i = 0;
	signed char	x, y;

	for (x = 0; x < MAX_DIM; x++) {
		for (y = 0; y < MAX_DIM; y++) {
			if (SAME_COLOR(state->b[x][y], color))
				i++;
		}
	}
	return i;
}

/*
 * Game is over when neither color can make a turn
 */
int game_is_over(const GAME_STATE *state) {
	const static CHIP_COLOR all_colors[] = {COLOR_NEG, COLOR_POS, COLOR_VACANT};
	GAME_TURN	t;
	const CHIP_COLOR  *color = all_colors;
	
	for (t.color = *color; t.color != COLOR_VACANT; t.color = *color++)
		for (t.x = 0; t.x < MAX_DIM; t.x++)
			for (t.y = 0; t.y < MAX_DIM; t.y++)
				if (validate_turn(state, &t) == E_OK)
					return 0;
	return 1;
}

/** our score will fit into 16bit val */
#define GAME_SCORE			short
#define GAME_SCORE_MAX		0x7FFF-1
#define GAME_SCORE_MIN		0x8000+1

/*
 * The estimated value for each field on the game board
 */
/* CHIP_COLOR == signed char */
static const CHIP_COLOR m_weight[MAX_DIM][MAX_DIM] = {
	{ 5, -1,  3,  3,  3,  3, -1,  5},
 
	{-1, -2, -1, -1, -1, -1, -2, -1},

	{ 3, -1,  1,  1,  1,  1, -1,  3},

	{ 3, -1,  1,  1,  1,  1, -1,  3},

	{ 3, -1,  1,  1,  1,  1, -1,  3},

	{ 3, -1,  1,  1,  1,  1, -1,  3},

	{-1, -2, -1, -1, -1, -1, -2, -1},

	{ 5, -1,  3,  3,  3,  3, -1,  5},

};

/*
 * Evaluate position 'state', using estimation matrix
 */
static GAME_SCORE game_eval(const GAME_STATE *state, CHIP_COLOR color) {
	GAME_SCORE eval = 0;
	signed char	i, j;
	
	for (i = 0; i < MAX_DIM; i++)
		for (j = 0; j < MAX_DIM; j++) 
			eval += state->b[i][j]*m_weight[i][j];
	return eval * color;
}

GAME_SCORE find_best_turn_intr(GAME_TURN *best_turn,
							   const GAME_STATE *state,
							   CHIP_COLOR color,
							   int depth,
							   GAME_SCORE simt,
							   int (*is_stop)(int depth, void *param),
							   void *is_stop_param)
{
	GAME_STATE	tmp_state;
	GAME_TURN	t, adv_best_turn;
	GAME_SCORE		ascore, best_score;
	char			turns_revised = 0;
	
	/* assume there are no turns */
	best_turn->x = -1;
	best_turn->y = -1;
	best_score = GAME_SCORE_MIN;

	if (is_stop && is_stop(depth, is_stop_param))
		return best_score;

	tmp_state = *state;
	t.color = color;
	for (t.x = 0; t.x < MAX_DIM; t.x++) {
		for (t.y = 0; t.y < MAX_DIM; t.y++) {
			if (make_turn(&tmp_state, &t)) {
				if (depth) {
					/* find best for contendor */
					ascore = -find_best_turn_intr(&adv_best_turn,
												  &tmp_state,
												  ALTER_COLOR(color),
												  depth-1,
												  -best_score,
												  is_stop,
												  is_stop_param);
				} else {
					ascore = game_eval(&tmp_state, color);
				}
				tmp_state = *state; /* undo make_turn() */
				turns_revised++;
				if (ascore > best_score) {
					best_score = ascore;
					*best_turn = t;
				}
#ifndef ALPHA_BETA_CUT_OFF
				/* Check for Alpha or Beta cut on the game tree */ 
				if (best_score > simt) {
					goto ret;
				}
#endif
			}
		}
	}
	if (!turns_revised) { /* No more turns found */
		if (depth) {
			/* try turn of the contendor */
			best_score = -find_best_turn_intr(&adv_best_turn,
											  &tmp_state,
											  ALTER_COLOR(color),
											  depth-1,
											  -simt,
											  is_stop,
											  is_stop_param);
		} else {
			/* 
			 * we've reached the final leaf and there are no possible turns,
			 * probably game is just over at this point
			 */
			best_score = (chips_count(state, color) - chips_count(state, ALTER_COLOR(color))) * 100;
		}
	}
ret:
	return (best_score);
}

GAME_SCORE find_best_turn(GAME_TURN *best_turn, 
							   const GAME_STATE *state,
							   CHIP_COLOR color,
							   int depth)
{
	return find_best_turn_intr(best_turn, state, color, depth, GAME_SCORE_MAX, 0, 0);
}

char color2abbr(CHIP_COLOR color) {
	static char abbr[3] = { 'B', '-', 'W' };
	return abbr[(color+1) % 3];
}

CHIP_COLOR abbr2color(char abbr) {
	return (abbr == '-' ? COLOR_VACANT : (abbr == 'W' ? COLOR_POS : COLOR_NEG));
}

void print_position(const GAME_STATE *state) {
	int		x, y;

	for (y = 0; y < MAX_DIM; y++) {
		for (x = 0; x < MAX_DIM; x++) {
			printf(" %c", color2abbr(state->b[x][y]));
		}
		printf("\n");
	}
}

void read_position(GAME_STATE *state, FILE *fin) {
	int		x = 0, y = 0;
	char	ch;

	while (!feof(fin)) {
		ch = fgetc(fin);
		switch(ch) {
		case 'B':
		case 'W':
		case '-':
			state->b[x++][y] = abbr2color(ch);
			break;
		case '\n':
			y++;
			x = 0;
			break;
		case EOF:
			return;
		}
	}
}

int main(int argc, char **argv) {
	FILE *fin = stdin;
	char c;
	c = fgetc(fin);
	CHIP_COLOR color = abbr2color(c);
	(void)fgetc(fin);
	GAME_STATE	state;
	read_position(&state, fin);
	if (game_is_over(&state)) {
		fprintf(stderr, "Game is over\n");
		print_position(&state);
		return 255;
	}
	GAME_TURN	turn = {COLOR_VACANT, 0, 0};
	const int srch_depth = 6;
	find_best_turn(&turn, &state, color, srch_depth);
	if (turn.x < 0) {
		fprintf(stderr, "There are no turns by color '%c'\n", color2abbr(color));
		print_position(&state);
		return 254;
	}
	printf("%d %d\n", (int)turn.y, (int)turn.x);
#if 0
	int e_code = make_turn(&state, &turn);
	fprintf(stderr, "We captured %d chip(s)\n", e_code);
	print_position(&state);
#endif
	return 0;
}
