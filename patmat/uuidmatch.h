#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char UMSTATE;

#define UMPATLEN	36

// start with automate position 0
void um_init(UMSTATE *state);

// return true when ch was the last char in uuid pattern
int um_match(UMSTATE *state, char ch);

#ifdef __cplusplus
}
#endif
