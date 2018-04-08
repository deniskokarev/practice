#ifdef __cplusplus
extern "C" {
#endif

enum {
	P_NONE,
	P_HEX,
	P_DASH,
	P_SZ
};

typedef unsigned char UMSTATE;

#define UMPATLEN	36

extern UMSTATE uuid_pattern[UMPATLEN+1][P_SZ];
	
// start with automate position 0
void um_init(UMSTATE *state);

// return true when ch was the last char in uuid pattern
int um_match(UMSTATE *state, char ch);

#ifdef __cplusplus
}
#endif
