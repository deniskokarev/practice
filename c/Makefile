BINS = a b c d e f \
	alg/comb_test \
	alg/heap_test \

INCGT = ./googletest/googletest/include
LIBGT = ./libgt/googlemock/gtest/libgtest.a
LIBGTMAIN = ./libgt/googlemock/gtest/libgtest_main.a

CXXFLAGS += -std=c++11 -Wall -g -O0 -I$(INCGT) 
CFLAGS += -std=c99 -Wall
LINK.o = $(LINK.cc)

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

alg/comb_test.o: alg/comb_test.cc
	$(CXX) $(CXXFLAGS) -I$(INCGT) -o $(@) -c $(?)

alg/comb_test: alg/comb.o alg/comb_test.o $(LIBGTMAIN) $(LIBGT)
	$(CXX) $(CXXFLAGS) -o $(@) $(+)

alg/heap_test.o: alg/heap.hh
alg/heap_test: alg/heap_test.o $(LIBGTMAIN) $(LIBGT)
	$(CXX) $(CXXFLAGS) -o $(@) $(+)

draft/knapsack_test: draft/knapsack_test.o draft/knapsack.o $(LIBGTMAIN) $(LIBGT)
	$(CXX) $(CXXFLAGS) -o $(@) $(+)

draft/matmul.o: draft/matmul.hh
draft/matmul_test.o: draft/matmul.hh
draft/matmul_test: draft/matmul_test.o draft/matmul.o $(LIBGTMAIN) $(LIBGT)
	$(CXX) $(CXXFLAGS) -o $(@) $(+)

test: ./alg/comb_test ./alg/heap_test
	./alg/comb_test
	./alg/heap_test
	./draft/knapsack_test
	./draft/mapmul_test

clean:
	for d in . alg draft; do rm -f $$d/*.o $$d/*~; done
	rm -rf libgt
	rm -f $(BINS)
	rm -rf Build
