BINS = a b c d e f \
	alg/choose \
	alg/choosem \
	alg/perm \
	alg/comb_test \
	alg/heap_test \

CXXFLAGS += -std=c++11 -Wall
CFLAGS += -std=c99 -Wall
LINK.o = $(LINK.cc)

INCGT = ./googletest/googletest/include
LIBGT = ./libgt/googlemock/gtest/libgtest.a
LIBGTMAIN = ./libgt/googlemock/gtest/libgtest_main.a

all: $(BINS)

$(LIBGTMAIN): $(LIBGT)
$(LIBGT):
	mkdir libgt
	cd libgt && cmake ../googletest && $(MAKE)

libgt: $(LIBGTMAIN)

# codeforces bins
cf: a b c d e f

a: a.o
b: b.o
c: c.o
d: d.o
e: e.o
f: f.o

alg/choose: alg/choose.o
alg/choosem: alg/choosem.o
alg/perm: alg/perm.o
alg/comb_test.o: alg/comb_test.cc
	$(CXX) $(CXXFLAGS) -I$(INCGT) -o $(@) -c $(?)
alg/comb_test: alg/comb.o alg/comb_test.o $(LIBGTMAIN) $(LIBGT)
	$(CXX) $(CXXFLAGS) -o $(@) $(+)
alg/heap_test.o: alg/heap_test.cc
	$(CXX) $(CXXFLAGS) -I$(INCGT) -o $(@) -c $(?)
alg/heap_test: alg/heap_test.o $(LIBGTMAIN) $(LIBGT)
	$(CXX) $(CXXFLAGS) -o $(@) $(+)

perm.o: perm.cc perm.hh
div7: div7.o
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
cf764a: cf764a.o

test: ./alg/comb_test ./alg/heap_test
	./alg/comb_test
	./alg/heap_test

clean:
	for d in . alg draft; do rm -f $$d/*.o $$d/*~; done
	rm -rf libgt
	rm -f $(BINS)
