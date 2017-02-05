CXXFLAGS = -std=c++11 -Wall -g -O0
#CXXFLAGS = -std=c++11 -Wall -O3
CFLAGS = -std=c99 -Wall -g -O0
LINK.o = $(LINK.cc)

BINS = a b c d e f \
	perm div7 choose choosem treap split safeseq derangement paths cf731c \
	4key atpp819 cf545d cf630f cf630g ringbuf heap \
	cf764a

all: $(BINS)

# codeforces bins
cf: a b c d e f

a: a.o
b: b.o
c: c.o
d: d.o
e: e.o
f: f.o

perm: perm.o
perm.o: perm.cc perm.hh
div7: div7.o
choose: choose.o
choosem: choosem.o
treap: treap.o
split: split.o
safeseq: safeseq.o
derangement: derangement.o
paths: paths.o
cf731c: cf731c.o
4key: 4key.o
atpp819: atpp819.o
cf545d: cf545d.o
cf630f: cf630f.o
cf630g: cf630g.o
ringbuf: ringbuf.o
heap: heap.o
cf764a: cf764a.o

test: all

clean:
	rm -f *.o *~
	rm -f $(BINS)
