CXXFLAGS = -std=c++11 -Wall -g -O0
#CXXFLAGS = -std=c++11 -Wall -O3
CFLAGS = -std=c99 -Wall -g -O0
LINK.o = $(LINK.cc)

BINS = perm div7 choose choosem treap split safeseq derangement paths cf731c

all: $(BINS)

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

test: all

clean:
	rm -f *.o
	rm -f $(BINS)
