#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define OK        0
#define NOMEM    -1
#define EMPTY    -2

typedef struct {
    uint64_t head, tail;
    uint64_t sz;
    char *buf;
} RINGBUF;

int init_ringbuf(RINGBUF *buf, int sz) {
    buf->head = 0;
    buf->tail = 0;
    buf->sz = sz;
    buf->buf = (char*)malloc(sz);
    return buf->buf != NULL;
}

void delete_ringbuf(RINGBUF *buf, int sz) {
    free(buf->buf);
}

int put_ringbuf(RINGBUF *buf, char c) {
    if (buf->head-buf->tail < buf->sz) {
        buf->buf[buf->head++] = c;
		return OK;
    } else {
        return NOMEM;
    }
}

int get_ringbuf(RINGBUF *buf, char *c) {
    if (buf->tail<buf->head) {
        *c = buf->buf[buf->tail++];
        return OK;
    } else {
        return EMPTY;
    }
}


int main(int argc, char **argv) {
    char *s = "Hello, world";
    RINGBUF buf;
    int rc = init_ringbuf(&buf, 1024);
    if (!rc) {
        fprintf(stderr, "no mem\n");
        exit(-1);
    }
    int i;
    for (i=0; i<strlen(s); i++) {
        put_ringbuf(&buf, s[i]);        
    }
    put_ringbuf(&buf, 0);
    char c;
    while ((rc=get_ringbuf(&buf, &c))==OK && c!=0) {
        fputc(c, stdout);
    }
    fputc('\n', stdout);
}
