/**
 * Aho-Corasic pattern matching automata
 * @author Denis Kokarev
 */

#include <stdlib.h>

#ifdef __cplusplus 
extern "C" {
#endif
	
/* we'll reserve 0 as NULL indicator */
#define ACT_ROOT	1

#define ACT_FILE_SIGNATURE	0x30379ca1

/* power 2 of the trie page [1,2,4,8] */
#define ACT_PAGE_P2		2

typedef struct tag_ACT_NODE {
	unsigned next[1<<ACT_PAGE_P2]; // where to go upon next char
	unsigned sufref; // continue to next match
	int val:31;
	unsigned char end:1;
} ACT_NODE;

typedef struct tag_ACT {
	ACT_NODE *nodes;
	size_t sz;
	int fd;
	const char *fname;
} ACT;

/**
 * mem map to the pre-created AC trie file
 * @return 0 - success
 */	
int act_attach_mmap(ACT *act, const char *fname);

/**
 * unmap to the pre-created AC trie file
 * @return 0 - success
 */	
int act_detach_mmap(const ACT *act);

/**
 * consume next char
 * @returns next automata node, where 1 means at root
 * only when at root, it is safe to refresh/reattach the trie
 */
unsigned act_next_char(const ACT_NODE *act, unsigned node, char ch);	

/**
 * iterate the sequence of all matches triggered by last char
 * NB: result_node will be spoiled
 * @return 1 when match was found, *val will be populated with value
 * @return 0 when no more matches
 */
int act_next_match(const ACT_NODE *act, unsigned *result_node, int *val);


#ifdef __cplusplus 
}
#endif
