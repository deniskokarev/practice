BINS = a b c d e f \
	alg/comb_test \
	alg/ilog_test \
	alg/heap_test \
	draft/knapsack_test \
	draft/matmul_test \
	draft/lcs_test \

INCGT = ./googletest/googletest/include
LIBGT = ./libgt/googlemock/gtest/libgtest.a
LIBGTMAIN = ./libgt/googlemock/gtest/libgtest_main.a

CXXFLAGS += -std=c++11 -Wall -g -O0 -I$(INCGT) 
CFLAGS += -std=c99 -Wall
LINK.o = $(LINK.cc)
LDFLAGS = -lpthread

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

alg/ilog.c: alg/ilog.h

alg/ilog.h:  alg/ilog.hh

alg/ilog.hh: alg/genilog.sh
	cd alg && ./genilog.sh

alg/ilog_test.o: alg/ilog_test.cc alg/ilog.hh
	$(CXX) $(CXXFLAGS) -I$(INCGT) -o $(@) -c alg/ilog_test.cc

alg/ilog_test: alg/ilog_test.o $(LIBGTMAIN) $(LIBGT)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(@) $(+)

alg/heap_test.o: alg/heap.hh
alg/heap_test: alg/heap_test.o $(LIBGTMAIN) $(LIBGT)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(@) $(+)

draft/knapsack.o: draft/knapsack.hh
draft/knapsack_test: draft/knapsack_test.o draft/knapsack.o $(LIBGTMAIN) $(LIBGT)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(@) $(+)

draft/matmul.o: draft/matmul.hh
draft/matmul_test.o: draft/matmul.hh
draft/matmul_test: draft/matmul_test.o draft/matmul.o $(LIBGTMAIN) $(LIBGT)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(@) $(+)

draft/lcs_test.o: draft/lcs.hh
draft/lcs_test: draft/lcs_test.o $(LIBGTMAIN) $(LIBGT)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(@) $(+)

test: ./alg/comb_test ./alg/ilog_test ./alg/heap_test ./draft/knapsack_test ./draft/matmul_test
	./alg/comb_test
	./alg/ilog_test
	./alg/heap_test
	./draft/knapsack_test
	./draft/matmul_test

clean:
	rm -f alg/ilog.c alg/ilog.h alg/ilog.hh
	for d in . alg draft; do rm -f $$d/*.o $$d/*~; done
	rm -rf libgt
	rm -f $(BINS)
	rm -rf Build
