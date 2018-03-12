#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include "act.h"

/**
 * mem map to the pre-created AC trie file
 * @return 0 - success
 */	
int act_attach_mmap(ACT *act, const char *fname) {
	act->fname = fname;
	act->fd = open(fname, O_RDONLY, 0);
	if (act->fd < 0)
		return -1;
	act->sz = lseek(act->fd, 0, SEEK_END);
	unsigned numrec = act->sz/sizeof(ACT_NODE);
	unsigned rem = act->sz - numrec*sizeof(ACT_NODE);
	if (numrec < 2 || rem != 0)
		return -3;
	lseek(act->fd, 0, SEEK_SET);
	act->nodes = (ACT_NODE*)mmap(NULL, act->sz, PROT_WRITE|PROT_EXEC, MAP_PRIVATE, act->fd, 0);
	if (act->nodes == MAP_FAILED)
		return -2;
	if (act->nodes[0].val != ACT_FILE_SIGNATURE)
		return -3;
	return 0;
}

/**
 * detach act trie and close file
 */
int act_detach_mmap(const ACT *act) {
	int rc = munmap(act->nodes, act->sz);
	if (rc != 0)
		return -3;
	close(act->fd);
	return 0;
}

/**
 * consume next char
 * @returns next automata node, where 1 means at root
 * only when at root, it is safe to refresh/reattach the trie
 */
unsigned act_next_char(const ACT_NODE *act, unsigned node, char ch) {
	return act[node].next[(unsigned char)ch];
}

/**
 * iterate the sequence of all matches triggered by last char
 * NB: result_node will be spoiled
 * @return 1 when match was found, *val will be populated with value
 * @return 0 when no more matches
 */
int act_next_match(const ACT_NODE *act, unsigned *result_node, int *val) {
	if (!act[*result_node].end)
		*result_node = act[*result_node].sufref;
	if (*result_node != ACT_ROOT) {
		*val = act[*result_node].val;
		*result_node = act[*result_node].sufref;
		return 1;
	} else {
		return 0;
	}
}
